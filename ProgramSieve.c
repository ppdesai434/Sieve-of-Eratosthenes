#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>



int main (int argc, char *argv[]) {

    int n=2000;

    long lcount=0, gcount=0,star, fin,i;

    int rank,p,size, proc0_size;
    double runtime;
if(argc==4)
{
n=atoi(argv[3]);
}
else{
printf("Please enter number to be calculated:");
return 0;
}
    MPI_Init (NULL, NULL);

    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    MPI_Comm_size (MPI_COMM_WORLD, &p);


    MPI_Barrier(MPI_COMM_WORLD);

    runtime = -MPI_Wtime();


    star = 2 + rank*(n-1)/p;
    fin = 1 + (rank+1)*(n-1)/p;
    size = fin - star + 1;


    proc0_size = (n-1)/p;

    if ((2 + proc0_size) < (long) sqrt((double) n)) {
        if (rank == 0)
            printf ("Too many processors to calc %d\n", n);
       MPI_Finalize();
        exit(1);
    }

    int j;

    for (j=star; j<=fin; j++){

     if (isitComposite(j)==0){
        printf(" %d ",j);
        lcount++;
     }
     }


         MPI_Reduce (&lcount, &gcount, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);


     runtime += MPI_Wtime();
     printf("Process %d completed\n", rank);

    if (rank == 0) {
            printf ("There are %ld primes less than or equal to %d\n", gcount, n);
        printf ("Total elapsed time:  %f seconds\n", runtime);
     }


     MPI_Finalize ();
     return 0;
   }


int isitComposite (int n){

int RVal=0;

if(n==1)
        RVal = 1;

   else if(n%2 == 0 && n!=2)
        RVal = 1;

    if(RVal != 1) {
   int j;
    for(j=3; j<n; j+=2) {
                if(n%j == 0 ){
                        RVal = 1;
                        break;
                }
                if(j*j>n) break;
            }
    }

if(RVal == 0)
    return 0;
else
    return 1;
}
