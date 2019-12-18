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
struct generic_pm_domain {unsigned int state_idx; int (* power_on ) (struct generic_pm_domain*) ;int max_off_time_changed; int /*<<< orphan*/  name; TYPE_1__* states; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {scalar_t__ power_on_latency_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int stub1 (struct generic_pm_domain*) ; 
 int stub2 (struct generic_pm_domain*) ; 

__attribute__((used)) static int _genpd_power_on(struct generic_pm_domain *genpd, bool timed)
{
	unsigned int state_idx = genpd->state_idx;
	ktime_t time_start;
	s64 elapsed_ns;
	int ret;

	if (!genpd->power_on)
		return 0;

	if (!timed)
		return genpd->power_on(genpd);

	time_start = ktime_get();
	ret = genpd->power_on(genpd);
	if (ret)
		return ret;

	elapsed_ns = ktime_to_ns(ktime_sub(ktime_get(), time_start));
	if (elapsed_ns <= genpd->states[state_idx].power_on_latency_ns)
		return ret;

	genpd->states[state_idx].power_on_latency_ns = elapsed_ns;
	genpd->max_off_time_changed = true;
	pr_debug("%s: Power-%s latency exceeded, new value %lld ns\n",
		 genpd->name, "on", elapsed_ns);

	return ret;
}