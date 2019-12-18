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
struct kinfo_proc {scalar_t__ ki_pid; scalar_t__ ki_stat; scalar_t__ ki_slptime; int ki_tdflags; int /*<<< orphan*/  ki_estcpu; } ;

/* Variables and functions */
#define  BOTH 130 
 int ISRUN (struct kinfo_proc*) ; 
#define  ONLYA 129 
#define  ONLYB 128 
 scalar_t__ SZOMB ; 
 int TDF_SINTR ; 
 int TESTAB (int,int) ; 

int
proc_compare(struct kinfo_proc *p1, struct kinfo_proc *p2)
{

	if (p1 == NULL)
		return (1);
	/*
	 * see if at least one of them is runnable
	 */
	switch (TESTAB(ISRUN(p1), ISRUN(p2))) {
	case ONLYA:
		return (0);
	case ONLYB:
		return (1);
	case BOTH:
		/*
		 * tie - favor one with highest recent cpu utilization
		 */
		if (p2->ki_estcpu > p1->ki_estcpu)
			return (1);
		if (p1->ki_estcpu > p2->ki_estcpu)
			return (0);
		return (p2->ki_pid > p1->ki_pid); /* tie - return highest pid */
	}
	/*
	 * weed out zombies
	 */
	switch (TESTAB(p1->ki_stat == SZOMB, p2->ki_stat == SZOMB)) {
	case ONLYA:
		return (1);
	case ONLYB:
		return (0);
	case BOTH:
		return (p2->ki_pid > p1->ki_pid); /* tie - return highest pid */
	}
	/*
	 * pick the one with the smallest sleep time
	 */
	if (p2->ki_slptime > p1->ki_slptime)
		return (0);
	if (p1->ki_slptime > p2->ki_slptime)
		return (1);
	/*
	 * favor one sleeping in a non-interruptible sleep
	 */
	if (p1->ki_tdflags & TDF_SINTR && (p2->ki_tdflags & TDF_SINTR) == 0)
		return (1);
	if (p2->ki_tdflags & TDF_SINTR && (p1->ki_tdflags & TDF_SINTR) == 0)
		return (0);
	return (p2->ki_pid > p1->ki_pid);	/* tie - return highest pid */
}