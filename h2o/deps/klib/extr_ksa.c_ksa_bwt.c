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
typedef  int saint_t ;

/* Variables and functions */
 int SAIS_MAIN (unsigned char*,int*,int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 

int SAIS_BWT(unsigned char *T, saint_t n, int k)
{
	saint_t *SA, i;
	int ret;
	if ((SA = malloc(n * sizeof(saint_t))) == 0) return -1;
	if ((ret = SAIS_MAIN(T, SA, n, k)) != 0) return ret;
	for (i = 0; i < n; ++i)
		if (SA[i]) SA[i] = T[SA[i] - 1]; // if SA[i]==0, SA[i]=0
	for (i = 0; i < n; ++i) T[i] = SA[i];
	free(SA);
	return 0;
}