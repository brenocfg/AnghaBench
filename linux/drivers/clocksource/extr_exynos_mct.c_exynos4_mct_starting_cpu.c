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
struct clock_event_device {int features; int rating; int irq; void* tick_resume; void* set_state_oneshot_stopped; void* set_state_oneshot; void* set_state_shutdown; int /*<<< orphan*/  set_state_periodic; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  name; } ;
struct mct_clock_event_device {scalar_t__ base; int /*<<< orphan*/  name; struct clock_event_device evt; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int CLOCK_EVT_FEAT_PERIODIC ; 
 int EIO ; 
 scalar_t__ EXYNOS4_MCT_L_BASE (unsigned int) ; 
 scalar_t__ MCT_INT_SPI ; 
 size_t MCT_L0_IRQ ; 
 scalar_t__ MCT_L_TCNTB_OFFSET ; 
 int TICK_BASE_CNT ; 
 int clk_rate ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int,int,int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_mct_write (int,scalar_t__) ; 
 int /*<<< orphan*/  exynos4_tick_set_next_event ; 
 int /*<<< orphan*/  irq_force_affinity (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mct_int_type ; 
 int /*<<< orphan*/ * mct_irqs ; 
 struct mct_clock_event_device* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  percpu_mct_tick ; 
 int /*<<< orphan*/  set_state_periodic ; 
 void* set_state_shutdown ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int) ; 

__attribute__((used)) static int exynos4_mct_starting_cpu(unsigned int cpu)
{
	struct mct_clock_event_device *mevt =
		per_cpu_ptr(&percpu_mct_tick, cpu);
	struct clock_event_device *evt = &mevt->evt;

	mevt->base = EXYNOS4_MCT_L_BASE(cpu);
	snprintf(mevt->name, sizeof(mevt->name), "mct_tick%d", cpu);

	evt->name = mevt->name;
	evt->cpumask = cpumask_of(cpu);
	evt->set_next_event = exynos4_tick_set_next_event;
	evt->set_state_periodic = set_state_periodic;
	evt->set_state_shutdown = set_state_shutdown;
	evt->set_state_oneshot = set_state_shutdown;
	evt->set_state_oneshot_stopped = set_state_shutdown;
	evt->tick_resume = set_state_shutdown;
	evt->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	evt->rating = 500;	/* use value higher than ARM arch timer */

	exynos4_mct_write(TICK_BASE_CNT, mevt->base + MCT_L_TCNTB_OFFSET);

	if (mct_int_type == MCT_INT_SPI) {

		if (evt->irq == -1)
			return -EIO;

		irq_force_affinity(evt->irq, cpumask_of(cpu));
		enable_irq(evt->irq);
	} else {
		enable_percpu_irq(mct_irqs[MCT_L0_IRQ], 0);
	}
	clockevents_config_and_register(evt, clk_rate / (TICK_BASE_CNT + 1),
					0xf, 0x7fffffff);

	return 0;
}