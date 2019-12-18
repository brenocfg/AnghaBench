#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_pctcpu; scalar_t__ ki_runtime; TYPE_1__ ki_start; } ;
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 struct kinfo_proc* get_old_proc (struct kinfo_proc*) ; 
 double pctdouble (int /*<<< orphan*/ ) ; 
 double previous_interval ; 
 TYPE_2__ previous_wall_time ; 

__attribute__((used)) static double
proc_calc_pctcpu(struct kinfo_proc *pp)
{
	const struct kinfo_proc *oldp;

	if (previous_interval != 0) {
		oldp = get_old_proc(pp);
		if (oldp != NULL)
			return ((double)(pp->ki_runtime - oldp->ki_runtime)
			    / previous_interval);

		/*
		 * If this process/thread was created during the previous
		 * interval, charge it's total runtime to the previous
		 * interval.
		 */
		else if (pp->ki_start.tv_sec > previous_wall_time.tv_sec ||
		    (pp->ki_start.tv_sec == previous_wall_time.tv_sec &&
		    pp->ki_start.tv_usec >= previous_wall_time.tv_usec))
			return ((double)pp->ki_runtime / previous_interval);
	}
	return (pctdouble(pp->ki_pctcpu));
}