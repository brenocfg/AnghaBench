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
struct work_struct {int dummy; } ;
struct rdt_resource {int dummy; } ;
struct rdt_domain {int /*<<< orphan*/  cqm_limbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQM_LIMBOCHECK_INTERVAL ; 
 size_t RDT_RESOURCE_L3 ; 
 int /*<<< orphan*/  __check_limbo (struct rdt_domain*,int) ; 
 struct rdt_domain* get_domain_from_cpu (int,struct rdt_resource*) ; 
 scalar_t__ has_busy_rmid (struct rdt_resource*,struct rdt_domain*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 struct rdt_resource* rdt_resources_all ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 int /*<<< orphan*/  schedule_delayed_work_on (int,int /*<<< orphan*/ *,unsigned long) ; 
 int smp_processor_id () ; 

void cqm_handle_limbo(struct work_struct *work)
{
	unsigned long delay = msecs_to_jiffies(CQM_LIMBOCHECK_INTERVAL);
	int cpu = smp_processor_id();
	struct rdt_resource *r;
	struct rdt_domain *d;

	mutex_lock(&rdtgroup_mutex);

	r = &rdt_resources_all[RDT_RESOURCE_L3];
	d = get_domain_from_cpu(cpu, r);

	if (!d) {
		pr_warn_once("Failure to get domain for limbo worker\n");
		goto out_unlock;
	}

	__check_limbo(d, false);

	if (has_busy_rmid(r, d))
		schedule_delayed_work_on(cpu, &d->cqm_limbo, delay);

out_unlock:
	mutex_unlock(&rdtgroup_mutex);
}