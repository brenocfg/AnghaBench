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
 int PRIO_MAX ; 
 int PRIO_MIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int getpriority (int,int) ; 
 scalar_t__ setpriority (int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int
donice(int which, int who, int prio, int incr)
{
	int oldprio;

	errno = 0;
	oldprio = getpriority(which, who);
	if (oldprio == -1 && errno) {
		warn("%d: getpriority", who);
		return (1);
	}
	if (incr)
		prio = oldprio + prio;
	if (prio > PRIO_MAX)
		prio = PRIO_MAX;
	if (prio < PRIO_MIN)
		prio = PRIO_MIN;
	if (setpriority(which, who, prio) < 0) {
		warn("%d: setpriority", who);
		return (1);
	}
	fprintf(stderr, "%d: old priority %d, new priority %d\n", who,
	    oldprio, prio);
	return (0);
}