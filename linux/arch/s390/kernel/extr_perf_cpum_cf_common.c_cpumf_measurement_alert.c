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
struct ext_code {int dummy; } ;
struct cpu_cf_events {int flags; int /*<<< orphan*/  alert; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 unsigned int CPU_MF_INT_CF_CACA ; 
 unsigned int CPU_MF_INT_CF_LCDA ; 
 unsigned int CPU_MF_INT_CF_MASK ; 
 unsigned int CPU_MF_INT_CF_MTDA ; 
 int /*<<< orphan*/  IRQEXT_CMC ; 
 int PMU_F_RESERVED ; 
 int /*<<< orphan*/  atomic64_or (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qctri (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumf_measurement_alert(struct ext_code ext_code,
				    unsigned int alert, unsigned long unused)
{
	struct cpu_cf_events *cpuhw;

	if (!(alert & CPU_MF_INT_CF_MASK))
		return;

	inc_irq_stat(IRQEXT_CMC);
	cpuhw = this_cpu_ptr(&cpu_cf_events);

	/* Measurement alerts are shared and might happen when the PMU
	 * is not reserved.  Ignore these alerts in this case. */
	if (!(cpuhw->flags & PMU_F_RESERVED))
		return;

	/* counter authorization change alert */
	if (alert & CPU_MF_INT_CF_CACA)
		qctri(&cpuhw->info);

	/* loss of counter data alert */
	if (alert & CPU_MF_INT_CF_LCDA)
		pr_err("CPU[%i] Counter data was lost\n", smp_processor_id());

	/* loss of MT counter data alert */
	if (alert & CPU_MF_INT_CF_MTDA)
		pr_warn("CPU[%i] MT counter data was lost\n",
			smp_processor_id());

	/* store alert for special handling by in-kernel users */
	atomic64_or(alert, &cpuhw->alert);
}