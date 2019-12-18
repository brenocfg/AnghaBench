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
typedef  scalar_t__ u64 ;
struct pt_regs {int dummy; } ;
struct cpu_hw_events {int enabled; int /*<<< orphan*/  active_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DM_NMI ; 
 int /*<<< orphan*/  APIC_LVTPC ; 
 int /*<<< orphan*/  INTEL_PMC_IDX_FIXED_BTS ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
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
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_pmu_handle_irq_v4(struct pt_regs *regs)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int handled = 0;
	bool bts = false;
	u64 status;
	int pmu_enabled = cpuc->enabled;
	int loops = 0;

	/* PMU has been disabled because of counter freezing */
	cpuc->enabled = 0;
	if (test_bit(INTEL_PMC_IDX_FIXED_BTS, cpuc->active_mask)) {
		bts = true;
		intel_bts_disable_local();
		handled = intel_pmu_drain_bts_buffer();
		handled += intel_bts_interrupt();
	}
	status = intel_pmu_get_status();
	if (!status)
		goto done;
again:
	intel_pmu_lbr_read();
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
done:
	/* Ack the PMI in the APIC */
	apic_write(APIC_LVTPC, APIC_DM_NMI);

	/*
	 * The counters start counting immediately while ack the status.
	 * Make it as close as possible to IRET. This avoids bogus
	 * freezing on Skylake CPUs.
	 */
	if (status) {
		intel_pmu_ack_status(status);
	} else {
		/*
		 * CPU may issues two PMIs very close to each other.
		 * When the PMI handler services the first one, the
		 * GLOBAL_STATUS is already updated to reflect both.
		 * When it IRETs, the second PMI is immediately
		 * handled and it sees clear status. At the meantime,
		 * there may be a third PMI, because the freezing bit
		 * isn't set since the ack in first PMI handlers.
		 * Double check if there is more work to be done.
		 */
		status = intel_pmu_get_status();
		if (status)
			goto again;
	}

	if (bts)
		intel_bts_enable_local();
	cpuc->enabled = pmu_enabled;
	return handled;
}