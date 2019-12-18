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
typedef  scalar_t__ u64 ;
struct pt_regs {int dummy; } ;
struct cpu_hw_events {int enabled; } ;
struct TYPE_2__ {scalar_t__ late_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DM_NMI ; 
 int /*<<< orphan*/  APIC_LVTPC ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  __intel_pmu_disable_all () ; 
 int /*<<< orphan*/  __intel_pmu_enable_all (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ handle_pmi_common (struct pt_regs*,scalar_t__) ; 
 int /*<<< orphan*/  intel_bts_disable_local () ; 
 int /*<<< orphan*/  intel_bts_enable_local () ; 
 scalar_t__ intel_bts_interrupt () ; 
 int /*<<< orphan*/  intel_pmu_ack_status (scalar_t__) ; 
 int intel_pmu_drain_bts_buffer () ; 
 scalar_t__ intel_pmu_get_status () ; 
 int /*<<< orphan*/  intel_pmu_lbr_read () ; 
 int /*<<< orphan*/  intel_pmu_reset () ; 
 int /*<<< orphan*/  perf_event_print_debug () ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int intel_pmu_handle_irq(struct pt_regs *regs)
{
	struct cpu_hw_events *cpuc;
	int loops;
	u64 status;
	int handled;
	int pmu_enabled;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * Save the PMU state.
	 * It needs to be restored when leaving the handler.
	 */
	pmu_enabled = cpuc->enabled;
	/*
	 * No known reason to not always do late ACK,
	 * but just in case do it opt-in.
	 */
	if (!x86_pmu.late_ack)
		apic_write(APIC_LVTPC, APIC_DM_NMI);
	intel_bts_disable_local();
	cpuc->enabled = 0;
	__intel_pmu_disable_all();
	handled = intel_pmu_drain_bts_buffer();
	handled += intel_bts_interrupt();
	status = intel_pmu_get_status();
	if (!status)
		goto done;

	loops = 0;
again:
	intel_pmu_lbr_read();
	intel_pmu_ack_status(status);
	if (++loops > 100) {
		static bool warned;

		if (!warned) {
			WARN(1, "perfevents: irq loop stuck!\n");
			perf_event_print_debug();
			warned = true;
		}
		intel_pmu_reset();
		goto done;
	}

	handled += handle_pmi_common(regs, status);

	/*
	 * Repeat if there is more work to be done:
	 */
	status = intel_pmu_get_status();
	if (status)
		goto again;

done:
	/* Only restore PMU state when it's active. See x86_pmu_disable(). */
	cpuc->enabled = pmu_enabled;
	if (pmu_enabled)
		__intel_pmu_enable_all(0, true);
	intel_bts_enable_local();

	/*
	 * Only unmask the NMI after the overflow counters
	 * have been reset. This avoids spurious NMIs on
	 * Haswell CPUs.
	 */
	if (x86_pmu.late_ack)
		apic_write(APIC_LVTPC, APIC_DM_NMI);
	return handled;
}