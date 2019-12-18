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
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  LFPTOD (int /*<<< orphan*/ *,double) ; 
 int NBUF ; 
 double average ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  stderr ; 

int
main(
	int argc,
	char *argv[]
	)
{
	l_fp tr;
	int i, j;
	double dtemp, gtod[NBUF];

	/*
	 * Force pages into memory
	 */
	for (i = 0; i < NBUF; i ++)
	    gtod[i] = 0;

	/*
	 * Construct gtod array
	 */
	for (i = 0; i < NBUF; i ++) {
		get_systime(&tr);
		LFPTOD(&tr, gtod[i]);
	}

	/*
	 * Write out gtod array for later processing with Matlab
	 */
	average = 0;
	for (i = 0; i < NBUF - 2; i++) {
		gtod[i] = gtod[i + 1] - gtod[i];
		printf("%13.9f\n", gtod[i]);
		average += gtod[i];
	}

	/*
	 * Sort the gtod array and display deciles
	 */
	for (i = 0; i < NBUF - 2; i++) {
		for (j = 0; j <= i; j++) {
			if (gtod[j] > gtod[i]) {
				dtemp = gtod[j];
				gtod[j] = gtod[i];
				gtod[i] = dtemp;
			}
		}
	}
	average = average / (NBUF - 2);
	fprintf(stderr, "Average %13.9f\n", average);
	fprintf(stderr, "First rank\n");
	for (i = 0; i < 10; i++)
		fprintf(stderr, "%2d %13.9f\n", i, gtod[i]);
	fprintf(stderr, "Last rank\n");
	for (i = NBUF - 12; i < NBUF - 2; i++)
		fprintf(stderr, "%2d %13.9f\n", i, gtod[i]);
	exit(0);
}