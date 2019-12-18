#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct kinfo_proc {scalar_t__ ki_runtime; } const kinfo_proc ;
struct TYPE_2__ {scalar_t__ ru_nvcsw; scalar_t__ ru_nivcsw; } ;

/* Variables and functions */
 scalar_t__ PCTCPU (struct kinfo_proc const*) ; 
 TYPE_1__* RU (struct kinfo_proc const*) ; 
 struct kinfo_proc const* get_old_proc (struct kinfo_proc const*) ; 

__attribute__((used)) static int
proc_used_cpu(struct kinfo_proc *pp)
{
	const struct kinfo_proc *oldp;

	oldp = get_old_proc(pp);
	if (oldp == NULL)
		return (PCTCPU(pp) != 0);
	return (pp->ki_runtime != oldp->ki_runtime ||
	    RU(pp)->ru_nvcsw != RU(oldp)->ru_nvcsw ||
	    RU(pp)->ru_nivcsw != RU(oldp)->ru_nivcsw);
}