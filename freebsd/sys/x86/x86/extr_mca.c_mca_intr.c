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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int CPUID_MCA ; 
 int /*<<< orphan*/  MCE ; 
 int MCG_STATUS_MCIP ; 
 int MCG_STATUS_RIPV ; 
 int /*<<< orphan*/  MSR_MCG_STATUS ; 
 int /*<<< orphan*/  MSR_P5_MC_ADDR ; 
 int /*<<< orphan*/  MSR_P5_MC_TYPE ; 
 int cpu_feature ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int mca_scan (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

void
mca_intr(void)
{
	uint64_t mcg_status;
	int recoverable, count;

	if (!(cpu_feature & CPUID_MCA)) {
		/*
		 * Just print the values of the old Pentium registers
		 * and panic.
		 */
		printf("MC Type: 0x%jx  Address: 0x%jx\n",
		    (uintmax_t)rdmsr(MSR_P5_MC_TYPE),
		    (uintmax_t)rdmsr(MSR_P5_MC_ADDR));
		panic("Machine check");
	}

	/* Scan the banks and check for any non-recoverable errors. */
	count = mca_scan(MCE, &recoverable);
	mcg_status = rdmsr(MSR_MCG_STATUS);
	if (!(mcg_status & MCG_STATUS_RIPV))
		recoverable = 0;

	if (!recoverable) {
		/*
		 * Only panic if the error was detected local to this CPU.
		 * Some errors will assert a machine check on all CPUs, but
		 * only certain CPUs will find a valid bank to log.
		 */
		while (count == 0)
			cpu_spinwait();

		panic("Unrecoverable machine check exception");
	}

	/* Clear MCIP. */
	wrmsr(MSR_MCG_STATUS, mcg_status & ~MCG_STATUS_MCIP);
}