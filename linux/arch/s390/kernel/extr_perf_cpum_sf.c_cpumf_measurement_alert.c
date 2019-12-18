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
struct ext_code {int dummy; } ;
struct cpu_hw_sf {int flags; int /*<<< orphan*/  qsi; TYPE_1__* event; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 unsigned int CPU_MF_INT_SF_IAE ; 
 unsigned int CPU_MF_INT_SF_ISE ; 
 unsigned int CPU_MF_INT_SF_LSDA ; 
 unsigned int CPU_MF_INT_SF_MASK ; 
 unsigned int CPU_MF_INT_SF_PRA ; 
 unsigned int CPU_MF_INT_SF_SACA ; 
 int /*<<< orphan*/  IRQEXT_CMS ; 
 int PMU_F_ERR_IBE ; 
 int PMU_F_ERR_LSDA ; 
 int PMU_F_IN_USE ; 
 int PMU_F_RESERVED ; 
 scalar_t__ SAMPL_DIAG_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,unsigned int) ; 
 int /*<<< orphan*/  hw_collect_aux (struct cpu_hw_sf*) ; 
 int /*<<< orphan*/  hw_perf_event_update (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  qsi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sf_disable () ; 
 int /*<<< orphan*/  sfdbg ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumf_measurement_alert(struct ext_code ext_code,
				    unsigned int alert, unsigned long unused)
{
	struct cpu_hw_sf *cpuhw;

	if (!(alert & CPU_MF_INT_SF_MASK))
		return;
	inc_irq_stat(IRQEXT_CMS);
	cpuhw = this_cpu_ptr(&cpu_hw_sf);

	/* Measurement alerts are shared and might happen when the PMU
	 * is not reserved.  Ignore these alerts in this case. */
	if (!(cpuhw->flags & PMU_F_RESERVED))
		return;

	/* The processing below must take care of multiple alert events that
	 * might be indicated concurrently. */

	/* Program alert request */
	if (alert & CPU_MF_INT_SF_PRA) {
		if (cpuhw->flags & PMU_F_IN_USE)
			if (SAMPL_DIAG_MODE(&cpuhw->event->hw))
				hw_collect_aux(cpuhw);
			else
				hw_perf_event_update(cpuhw->event, 0);
		else
			WARN_ON_ONCE(!(cpuhw->flags & PMU_F_IN_USE));
	}

	/* Report measurement alerts only for non-PRA codes */
	if (alert != CPU_MF_INT_SF_PRA)
		debug_sprintf_event(sfdbg, 6, "measurement alert: %#x\n",
				    alert);

	/* Sampling authorization change request */
	if (alert & CPU_MF_INT_SF_SACA)
		qsi(&cpuhw->qsi);

	/* Loss of sample data due to high-priority machine activities */
	if (alert & CPU_MF_INT_SF_LSDA) {
		pr_err("Sample data was lost\n");
		cpuhw->flags |= PMU_F_ERR_LSDA;
		sf_disable();
	}

	/* Invalid sampling buffer entry */
	if (alert & (CPU_MF_INT_SF_IAE|CPU_MF_INT_SF_ISE)) {
		pr_err("A sampling buffer entry is incorrect (alert=0x%x)\n",
		       alert);
		cpuhw->flags |= PMU_F_ERR_IBE;
		sf_disable();
	}
}