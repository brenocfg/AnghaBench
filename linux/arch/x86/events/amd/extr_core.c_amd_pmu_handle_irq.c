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
struct pt_regs {int dummy; } ;
struct cpu_hw_events {int /*<<< orphan*/  active_mask; } ;

/* Variables and functions */
 int NMI_DONE ; 
 int NMI_HANDLED ; 
 int /*<<< orphan*/  X86_PMC_IDX_MAX ; 
 int __bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  perf_nmi_tstamp ; 
 scalar_t__ perf_nmi_window ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ time_after (scalar_t__,int /*<<< orphan*/ ) ; 
 int x86_pmu_handle_irq (struct pt_regs*) ; 

__attribute__((used)) static int amd_pmu_handle_irq(struct pt_regs *regs)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int active, handled;

	/*
	 * Obtain the active count before calling x86_pmu_handle_irq() since
	 * it is possible that x86_pmu_handle_irq() may make a counter
	 * inactive (through x86_pmu_stop).
	 */
	active = __bitmap_weight(cpuc->active_mask, X86_PMC_IDX_MAX);

	/* Process any counter overflows */
	handled = x86_pmu_handle_irq(regs);

	/*
	 * If a counter was handled, record a timestamp such that un-handled
	 * NMIs will be claimed if arriving within that window.
	 */
	if (handled) {
		this_cpu_write(perf_nmi_tstamp,
			       jiffies + perf_nmi_window);

		return handled;
	}

	if (time_after(jiffies, this_cpu_read(perf_nmi_tstamp)))
		return NMI_DONE;

	return NMI_HANDLED;
}