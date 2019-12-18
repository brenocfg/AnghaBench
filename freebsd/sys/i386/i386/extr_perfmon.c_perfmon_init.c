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

/* Variables and functions */
#define  CPUCLASS_586 129 
#define  CPUCLASS_686 128 
 int /*<<< orphan*/  MSR_EVNTSEL0 ; 
 int /*<<< orphan*/  MSR_EVNTSEL1 ; 
 int /*<<< orphan*/  MSR_P5_CESR ; 
 int /*<<< orphan*/  MSR_P5_CTR0 ; 
 int /*<<< orphan*/  MSR_P5_CTR1 ; 
 int /*<<< orphan*/  MSR_PERFCTR0 ; 
 int /*<<< orphan*/  MSR_PERFCTR1 ; 
 int cpu_class ; 
 int /*<<< orphan*/ * msr_ctl ; 
 int /*<<< orphan*/ * msr_pmc ; 
 int perfmon_cpuok ; 
 int /*<<< orphan*/  writectl ; 
 int /*<<< orphan*/  writectl5 ; 
 int /*<<< orphan*/  writectl6 ; 

void
perfmon_init(void)
{
#ifndef SMP
	switch(cpu_class) {
	case CPUCLASS_586:
		perfmon_cpuok = 1;
		msr_ctl[0] = MSR_P5_CESR;
		msr_ctl[1] = MSR_P5_CESR;
		msr_pmc[0] = MSR_P5_CTR0;
		msr_pmc[1] = MSR_P5_CTR1;
		writectl = writectl5;
		break;
	case CPUCLASS_686:
		perfmon_cpuok = 1;
		msr_ctl[0] = MSR_EVNTSEL0;
		msr_ctl[1] = MSR_EVNTSEL1;
		msr_pmc[0] = MSR_PERFCTR0;
		msr_pmc[1] = MSR_PERFCTR1;
		writectl = writectl6;
		break;

	default:
		perfmon_cpuok = 0;
		break;
	}
#endif /* SMP */
}