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
struct TYPE_3__ {int /*<<< orphan*/  rmid; } ;
struct rdtgroup {TYPE_1__ mon; int /*<<< orphan*/  cpu_mask; } ;
struct TYPE_4__ {scalar_t__ alloc_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 size_t RDT_RESOURCE_L2DATA ; 
 size_t RDT_RESOURCE_L3DATA ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_rmid (int /*<<< orphan*/ ) ; 
 scalar_t__ get_prefetch_disable_bits () ; 
 scalar_t__ prefetch_disable_bits ; 
 int pseudo_lock_init (struct rdtgroup*) ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 TYPE_2__* rdt_resources_all ; 
 struct rdtgroup rdtgroup_default ; 
 int /*<<< orphan*/  rdtgroup_locksetup_user_restore (struct rdtgroup*) ; 
 scalar_t__ rdtgroup_locksetup_user_restrict (struct rdtgroup*) ; 
 scalar_t__ rdtgroup_monitor_in_progress (struct rdtgroup*) ; 
 scalar_t__ rdtgroup_tasks_assigned (struct rdtgroup*) ; 

int rdtgroup_locksetup_enter(struct rdtgroup *rdtgrp)
{
	int ret;

	/*
	 * The default resource group can neither be removed nor lose the
	 * default closid associated with it.
	 */
	if (rdtgrp == &rdtgroup_default) {
		rdt_last_cmd_puts("Cannot pseudo-lock default group\n");
		return -EINVAL;
	}

	/*
	 * Cache Pseudo-locking not supported when CDP is enabled.
	 *
	 * Some things to consider if you would like to enable this
	 * support (using L3 CDP as example):
	 * - When CDP is enabled two separate resources are exposed,
	 *   L3DATA and L3CODE, but they are actually on the same cache.
	 *   The implication for pseudo-locking is that if a
	 *   pseudo-locked region is created on a domain of one
	 *   resource (eg. L3CODE), then a pseudo-locked region cannot
	 *   be created on that same domain of the other resource
	 *   (eg. L3DATA). This is because the creation of a
	 *   pseudo-locked region involves a call to wbinvd that will
	 *   affect all cache allocations on particular domain.
	 * - Considering the previous, it may be possible to only
	 *   expose one of the CDP resources to pseudo-locking and
	 *   hide the other. For example, we could consider to only
	 *   expose L3DATA and since the L3 cache is unified it is
	 *   still possible to place instructions there are execute it.
	 * - If only one region is exposed to pseudo-locking we should
	 *   still keep in mind that availability of a portion of cache
	 *   for pseudo-locking should take into account both resources.
	 *   Similarly, if a pseudo-locked region is created in one
	 *   resource, the portion of cache used by it should be made
	 *   unavailable to all future allocations from both resources.
	 */
	if (rdt_resources_all[RDT_RESOURCE_L3DATA].alloc_enabled ||
	    rdt_resources_all[RDT_RESOURCE_L2DATA].alloc_enabled) {
		rdt_last_cmd_puts("CDP enabled\n");
		return -EINVAL;
	}

	/*
	 * Not knowing the bits to disable prefetching implies that this
	 * platform does not support Cache Pseudo-Locking.
	 */
	prefetch_disable_bits = get_prefetch_disable_bits();
	if (prefetch_disable_bits == 0) {
		rdt_last_cmd_puts("Pseudo-locking not supported\n");
		return -EINVAL;
	}

	if (rdtgroup_monitor_in_progress(rdtgrp)) {
		rdt_last_cmd_puts("Monitoring in progress\n");
		return -EINVAL;
	}

	if (rdtgroup_tasks_assigned(rdtgrp)) {
		rdt_last_cmd_puts("Tasks assigned to resource group\n");
		return -EINVAL;
	}

	if (!cpumask_empty(&rdtgrp->cpu_mask)) {
		rdt_last_cmd_puts("CPUs assigned to resource group\n");
		return -EINVAL;
	}

	if (rdtgroup_locksetup_user_restrict(rdtgrp)) {
		rdt_last_cmd_puts("Unable to modify resctrl permissions\n");
		return -EIO;
	}

	ret = pseudo_lock_init(rdtgrp);
	if (ret) {
		rdt_last_cmd_puts("Unable to init pseudo-lock region\n");
		goto out_release;
	}

	/*
	 * If this system is capable of monitoring a rmid would have been
	 * allocated when the control group was created. This is not needed
	 * anymore when this group would be used for pseudo-locking. This
	 * is safe to call on platforms not capable of monitoring.
	 */
	free_rmid(rdtgrp->mon.rmid);

	ret = 0;
	goto out;

out_release:
	rdtgroup_locksetup_user_restore(rdtgrp);
out:
	return ret;
}