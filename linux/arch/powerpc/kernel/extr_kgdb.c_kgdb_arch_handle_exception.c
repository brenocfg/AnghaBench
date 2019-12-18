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
struct pt_regs {unsigned long nip; int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 int DBCR0_IC ; 
 int DBCR0_IDM ; 
 int /*<<< orphan*/  MSR_DE ; 
 int /*<<< orphan*/  MSR_SE ; 
 int /*<<< orphan*/  SPRN_DBCR0 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kgdb_cpu_doing_single_step ; 
 int /*<<< orphan*/  kgdb_hex2long (char**,unsigned long*) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 

int kgdb_arch_handle_exception(int vector, int signo, int err_code,
			       char *remcom_in_buffer, char *remcom_out_buffer,
			       struct pt_regs *linux_regs)
{
	char *ptr = &remcom_in_buffer[1];
	unsigned long addr;

	switch (remcom_in_buffer[0]) {
		/*
		 * sAA..AA   Step one instruction from AA..AA
		 * This will return an error to gdb ..
		 */
	case 's':
	case 'c':
		/* handle the optional parameter */
		if (kgdb_hex2long(&ptr, &addr))
			linux_regs->nip = addr;

		atomic_set(&kgdb_cpu_doing_single_step, -1);
		/* set the trace bit if we're stepping */
		if (remcom_in_buffer[0] == 's') {
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
			mtspr(SPRN_DBCR0,
			      mfspr(SPRN_DBCR0) | DBCR0_IC | DBCR0_IDM);
			linux_regs->msr |= MSR_DE;
#else
			linux_regs->msr |= MSR_SE;
#endif
			atomic_set(&kgdb_cpu_doing_single_step,
				   raw_smp_processor_id());
		}
		return 0;
	}

	return -1;
}