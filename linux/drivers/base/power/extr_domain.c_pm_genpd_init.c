#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  start; int /*<<< orphan*/  stop; } ;
struct TYPE_4__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  restore_noirq; int /*<<< orphan*/  poweroff_noirq; int /*<<< orphan*/  thaw_noirq; int /*<<< orphan*/  freeze_noirq; int /*<<< orphan*/  resume_noirq; int /*<<< orphan*/  suspend_noirq; int /*<<< orphan*/  prepare; int /*<<< orphan*/  runtime_resume; int /*<<< orphan*/  runtime_suspend; } ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct generic_pm_domain {int max_off_time_ns; int max_off_time_changed; int has_provider; int flags; int state_count; int /*<<< orphan*/  gpd_list_node; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  cpus; TYPE_3__ dev_ops; TYPE_2__ domain; int /*<<< orphan*/  accounting_time; int /*<<< orphan*/ * provider; scalar_t__ device_count; int /*<<< orphan*/  status; int /*<<< orphan*/  sd_count; int /*<<< orphan*/  power_off_work; struct dev_power_governor* gov; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  slave_links; int /*<<< orphan*/  master_links; } ;
struct dev_power_governor {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GENPD_FLAG_PM_CLK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPD_STATE_ACTIVE ; 
 int /*<<< orphan*/  GPD_STATE_POWER_OFF ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genpd_complete ; 
 int /*<<< orphan*/  genpd_freeze_noirq ; 
 scalar_t__ genpd_is_always_on (struct generic_pm_domain*) ; 
 scalar_t__ genpd_is_cpu_domain (struct generic_pm_domain*) ; 
 scalar_t__ genpd_is_rpm_always_on (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  genpd_lock_init (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  genpd_power_off_work_fn ; 
 int /*<<< orphan*/  genpd_poweroff_noirq ; 
 int /*<<< orphan*/  genpd_prepare ; 
 int /*<<< orphan*/  genpd_restore_noirq ; 
 int /*<<< orphan*/  genpd_resume_noirq ; 
 int /*<<< orphan*/  genpd_runtime_resume ; 
 int /*<<< orphan*/  genpd_runtime_suspend ; 
 int genpd_set_default_power_state (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  genpd_status_on (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  genpd_suspend_noirq ; 
 int /*<<< orphan*/  genpd_thaw_noirq ; 
 int /*<<< orphan*/  gpd_list ; 
 int /*<<< orphan*/  gpd_list_lock ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_clk_resume ; 
 int /*<<< orphan*/  pm_clk_suspend ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pm_genpd_init(struct generic_pm_domain *genpd,
		  struct dev_power_governor *gov, bool is_off)
{
	int ret;

	if (IS_ERR_OR_NULL(genpd))
		return -EINVAL;

	INIT_LIST_HEAD(&genpd->master_links);
	INIT_LIST_HEAD(&genpd->slave_links);
	INIT_LIST_HEAD(&genpd->dev_list);
	genpd_lock_init(genpd);
	genpd->gov = gov;
	INIT_WORK(&genpd->power_off_work, genpd_power_off_work_fn);
	atomic_set(&genpd->sd_count, 0);
	genpd->status = is_off ? GPD_STATE_POWER_OFF : GPD_STATE_ACTIVE;
	genpd->device_count = 0;
	genpd->max_off_time_ns = -1;
	genpd->max_off_time_changed = true;
	genpd->provider = NULL;
	genpd->has_provider = false;
	genpd->accounting_time = ktime_get();
	genpd->domain.ops.runtime_suspend = genpd_runtime_suspend;
	genpd->domain.ops.runtime_resume = genpd_runtime_resume;
	genpd->domain.ops.prepare = genpd_prepare;
	genpd->domain.ops.suspend_noirq = genpd_suspend_noirq;
	genpd->domain.ops.resume_noirq = genpd_resume_noirq;
	genpd->domain.ops.freeze_noirq = genpd_freeze_noirq;
	genpd->domain.ops.thaw_noirq = genpd_thaw_noirq;
	genpd->domain.ops.poweroff_noirq = genpd_poweroff_noirq;
	genpd->domain.ops.restore_noirq = genpd_restore_noirq;
	genpd->domain.ops.complete = genpd_complete;

	if (genpd->flags & GENPD_FLAG_PM_CLK) {
		genpd->dev_ops.stop = pm_clk_suspend;
		genpd->dev_ops.start = pm_clk_resume;
	}

	/* Always-on domains must be powered on at initialization. */
	if ((genpd_is_always_on(genpd) || genpd_is_rpm_always_on(genpd)) &&
			!genpd_status_on(genpd))
		return -EINVAL;

	if (genpd_is_cpu_domain(genpd) &&
	    !zalloc_cpumask_var(&genpd->cpus, GFP_KERNEL))
		return -ENOMEM;

	/* Use only one "off" state if there were no states declared */
	if (genpd->state_count == 0) {
		ret = genpd_set_default_power_state(genpd);
		if (ret) {
			if (genpd_is_cpu_domain(genpd))
				free_cpumask_var(genpd->cpus);
			return ret;
		}
	} else if (!gov && genpd->state_count > 1) {
		pr_warn("%s: no governor for states\n", genpd->name);
	}

	device_initialize(&genpd->dev);
	dev_set_name(&genpd->dev, "%s", genpd->name);

	mutex_lock(&gpd_list_lock);
	list_add(&genpd->gpd_list_node, &gpd_list);
	mutex_unlock(&gpd_list_lock);

	return 0;
}