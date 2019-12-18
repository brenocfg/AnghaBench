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
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,int,int) ; 
 int /*<<< orphan*/  quit (char*) ; 
 int sched_get_priority_max (int) ; 
 int sched_get_priority_min (int) ; 
 char* sched_text (int) ; 
 scalar_t__ stderr ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
checkpris(int sched)
{
	int smin;
	int smax;

	errno = 0;

	if ( (smin = sched_get_priority_min(sched)) == -1 && errno)
		quit("sched_get_priority_min");

	if ( (smax = sched_get_priority_max(sched)) == -1 && errno)
		quit("sched_get_priority_max");

	if (smax - smin + 1 < 32 || smax < smin) {
		fprintf(stderr, "Illegal priority range for %s: %d to %d\n",
		sched_text(sched), smin, smax);
		exit(-1);
	}

	if (verbose)
		fprintf(verbose, "%12s: sched_min %2d sched_max %2d\n",
		sched_text(sched), smin, smax);
}