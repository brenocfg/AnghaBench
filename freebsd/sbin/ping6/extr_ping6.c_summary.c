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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* hostname ; 
 double nrcvtimeout ; 
 int nreceived ; 
 double nrepeats ; 
 int ntransmitted ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 double sqrt (double) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ timing ; 
 double tmax ; 
 double tmin ; 
 double tsum ; 
 double tsumsq ; 

__attribute__((used)) static void
summary(void)
{

	(void)printf("\n--- %s ping6 statistics ---\n", hostname);
	(void)printf("%ld packets transmitted, ", ntransmitted);
	(void)printf("%ld packets received, ", nreceived);
	if (nrepeats)
		(void)printf("+%ld duplicates, ", nrepeats);
	if (ntransmitted) {
		if (nreceived > ntransmitted)
			(void)printf("-- somebody's duplicating packets!");
		else
			(void)printf("%.1f%% packet loss",
			    ((((double)ntransmitted - nreceived) * 100.0) /
			    ntransmitted));
	}
	if (nrcvtimeout)
		printf(", %ld packets out of wait time", nrcvtimeout);
	(void)putchar('\n');
	if (nreceived && timing) {
		/* Only display average to microseconds */
		double num = nreceived + nrepeats;
		double avg = tsum / num;
		double dev = sqrt(tsumsq / num - avg * avg);
		(void)printf(
		    "round-trip min/avg/max/std-dev = %.3f/%.3f/%.3f/%.3f ms\n",
		    tmin, avg, tmax, dev);
		(void)fflush(stdout);
	}
	(void)fflush(stdout);
}