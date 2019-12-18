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
struct rdt_resource {int /*<<< orphan*/  cache_level; } ;
struct rdt_domain {int mbm_work_cpu; int cqm_work_cpu; int /*<<< orphan*/  cqm_limbo; int /*<<< orphan*/  mbm_over; struct rdt_domain* mbm_local; struct rdt_domain* mbm_total; int /*<<< orphan*/  rmid_busy_llc; struct rdt_domain* mbps_val; struct rdt_domain* ctrl_val; TYPE_1__* plr; int /*<<< orphan*/  list; int /*<<< orphan*/  id; int /*<<< orphan*/  cpu_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/ * d; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct rdt_domain*) ; 
 size_t RDT_RESOURCE_L3 ; 
 int /*<<< orphan*/  __check_limbo (struct rdt_domain*,int) ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cqm_setup_limbo_handler (struct rdt_domain*,int /*<<< orphan*/ ) ; 
 int get_cache_id (int,int /*<<< orphan*/ ) ; 
 scalar_t__ has_busy_rmid (struct rdt_resource*,struct rdt_domain*) ; 
 scalar_t__ is_llc_occupancy_enabled () ; 
 scalar_t__ is_mbm_enabled () ; 
 int /*<<< orphan*/  kfree (struct rdt_domain*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbm_setup_overflow_handler (struct rdt_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 struct rdt_domain* rdt_find_domain (struct rdt_resource*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdt_mon_enable_key ; 
 struct rdt_resource* rdt_resources_all ; 
 int /*<<< orphan*/  rmdir_mondata_subdir_allrdtgrp (struct rdt_resource*,int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void domain_remove_cpu(int cpu, struct rdt_resource *r)
{
	int id = get_cache_id(cpu, r->cache_level);
	struct rdt_domain *d;

	d = rdt_find_domain(r, id, NULL);
	if (IS_ERR_OR_NULL(d)) {
		pr_warn("Could't find cache id for cpu %d\n", cpu);
		return;
	}

	cpumask_clear_cpu(cpu, &d->cpu_mask);
	if (cpumask_empty(&d->cpu_mask)) {
		/*
		 * If resctrl is mounted, remove all the
		 * per domain monitor data directories.
		 */
		if (static_branch_unlikely(&rdt_mon_enable_key))
			rmdir_mondata_subdir_allrdtgrp(r, d->id);
		list_del(&d->list);
		if (is_mbm_enabled())
			cancel_delayed_work(&d->mbm_over);
		if (is_llc_occupancy_enabled() &&  has_busy_rmid(r, d)) {
			/*
			 * When a package is going down, forcefully
			 * decrement rmid->ebusy. There is no way to know
			 * that the L3 was flushed and hence may lead to
			 * incorrect counts in rare scenarios, but leaving
			 * the RMID as busy creates RMID leaks if the
			 * package never comes back.
			 */
			__check_limbo(d, true);
			cancel_delayed_work(&d->cqm_limbo);
		}

		/*
		 * rdt_domain "d" is going to be freed below, so clear
		 * its pointer from pseudo_lock_region struct.
		 */
		if (d->plr)
			d->plr->d = NULL;

		kfree(d->ctrl_val);
		kfree(d->mbps_val);
		bitmap_free(d->rmid_busy_llc);
		kfree(d->mbm_total);
		kfree(d->mbm_local);
		kfree(d);
		return;
	}

	if (r == &rdt_resources_all[RDT_RESOURCE_L3]) {
		if (is_mbm_enabled() && cpu == d->mbm_work_cpu) {
			cancel_delayed_work(&d->mbm_over);
			mbm_setup_overflow_handler(d, 0);
		}
		if (is_llc_occupancy_enabled() && cpu == d->cqm_work_cpu &&
		    has_busy_rmid(r, d)) {
			cancel_delayed_work(&d->cqm_limbo);
			cqm_setup_limbo_handler(d, 0);
		}
	}
}