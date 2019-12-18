#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int BUCKET_A_SIZE ; 
 int BUCKET_B_SIZE ; 
 int construct_BWT (unsigned char const*,int*,int*,int*,int,int) ; 
 int construct_BWT_indexes (unsigned char const*,int*,int*,int*,int,int,unsigned char*,int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int sort_typeBstar (unsigned char const*,int*,int*,int*,int,int) ; 

int
divbwt(const unsigned char *T, unsigned char *U, int *A, int n, unsigned char * num_indexes, int * indexes, int openMP) {
  int *B;
  int *bucket_A, *bucket_B;
  int m, pidx, i;

  /* Check arguments. */
  if((T == NULL) || (U == NULL) || (n < 0)) { return -1; }
  else if(n <= 1) { if(n == 1) { U[0] = T[0]; } return n; }

  if((B = A) == NULL) { B = (int *)malloc((size_t)(n + 1) * sizeof(int)); }
  bucket_A = (int *)malloc(BUCKET_A_SIZE * sizeof(int));
  bucket_B = (int *)malloc(BUCKET_B_SIZE * sizeof(int));

  /* Burrows-Wheeler Transform. */
  if((B != NULL) && (bucket_A != NULL) && (bucket_B != NULL)) {
    m = sort_typeBstar(T, B, bucket_A, bucket_B, n, openMP);

    if (num_indexes == NULL || indexes == NULL) {
        pidx = construct_BWT(T, B, bucket_A, bucket_B, n, m);
    } else {
        pidx = construct_BWT_indexes(T, B, bucket_A, bucket_B, n, m, num_indexes, indexes);
    }

    /* Copy to output string. */
    U[0] = T[n - 1];
    for(i = 0; i < pidx; ++i) { U[i + 1] = (unsigned char)B[i]; }
    for(i += 1; i < n; ++i) { U[i] = (unsigned char)B[i]; }
    pidx += 1;
  } else {
    pidx = -2;
  }

  free(bucket_B);
  free(bucket_A);
  if(A == NULL) { free(B); }

  return pidx;
}