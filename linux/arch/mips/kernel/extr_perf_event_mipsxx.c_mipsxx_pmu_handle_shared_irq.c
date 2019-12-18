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
typedef  int u64 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct cpu_hw_events {int /*<<< orphan*/  used_mask; } ;
struct TYPE_2__ {unsigned int num_counters; int (* read_counter ) (int) ;int overflow; } ;

/* Variables and functions */
 int CAUSEF_PCI ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 scalar_t__ cpu_has_perf_cntr_intr_bit ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/  handle_associated_event (struct cpu_hw_events*,int,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  irq_work_run () ; 
 TYPE_1__ mipspmu ; 
 int /*<<< orphan*/  pause_local_counters () ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmuint_rwlock ; 
 int read_c0_cause () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resume_local_counters () ; 
 int stub1 (int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipsxx_pmu_handle_shared_irq(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct perf_sample_data data;
	unsigned int counters = mipspmu.num_counters;
	u64 counter;
	int n, handled = IRQ_NONE;
	struct pt_regs *regs;

	if (cpu_has_perf_cntr_intr_bit && !(read_c0_cause() & CAUSEF_PCI))
		return handled;
	/*
	 * First we pause the local counters, so that when we are locked
	 * here, the counters are all paused. When it gets locked due to
	 * perf_disable(), the timer interrupt handler will be delayed.
	 *
	 * See also mipsxx_pmu_start().
	 */
	pause_local_counters();
#ifdef CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	read_lock(&pmuint_rwlock);
#endif

	regs = get_irq_regs();

	perf_sample_data_init(&data, 0, 0);

	for (n = counters - 1; n >= 0; n--) {
		if (!test_bit(n, cpuc->used_mask))
			continue;

		counter = mipspmu.read_counter(n);
		if (!(counter & mipspmu.overflow))
			continue;

		handle_associated_event(cpuc, n, &data, regs);
		handled = IRQ_HANDLED;
	}

#ifdef CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	read_unlock(&pmuint_rwlock);
#endif
	resume_local_counters();

	/*
	 * Do all the work for the pending perf events. We can do this
	 * in here because the performance counter interrupt is a regular
	 * interrupt, not NMI.
	 */
	if (handled == IRQ_HANDLED)
		irq_work_run();

	return handled;
}