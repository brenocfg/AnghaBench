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
struct hrtimer {int dummy; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_NORESTART ; 
 int HRTIMER_RESTART ; 
 int NMI_WATCHDOG_ENABLED ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_forward_now (struct hrtimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ktime (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  watchdog_cpumask ; 
 int watchdog_enabled ; 
 int /*<<< orphan*/  watchdog_timer_interrupt (int) ; 
 int /*<<< orphan*/  wd_timer_period_ms ; 

__attribute__((used)) static enum hrtimer_restart watchdog_timer_fn(struct hrtimer *hrtimer)
{
	int cpu = smp_processor_id();

	if (!(watchdog_enabled & NMI_WATCHDOG_ENABLED))
		return HRTIMER_NORESTART;

	if (!cpumask_test_cpu(cpu, &watchdog_cpumask))
		return HRTIMER_NORESTART;

	watchdog_timer_interrupt(cpu);

	hrtimer_forward_now(hrtimer, ms_to_ktime(wd_timer_period_ms));

	return HRTIMER_RESTART;
}