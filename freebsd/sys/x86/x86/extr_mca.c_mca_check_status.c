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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
struct mca_record {int mr_status; int mr_bank; void* mr_cpu; int /*<<< orphan*/  mr_cpu_vendor_id; int /*<<< orphan*/  mr_cpu_id; void* mr_mcg_status; void* mr_mcg_cap; void* mr_apic_id; int /*<<< orphan*/  mr_tsc; void* mr_misc; void* mr_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* status ) (int) ;int /*<<< orphan*/  (* misc ) (int) ;int /*<<< orphan*/  (* addr ) (int) ;} ;

/* Variables and functions */
 int MC_STATUS_ADDRV ; 
 int MC_STATUS_MISCV ; 
 int MC_STATUS_PCC ; 
 int MC_STATUS_UC ; 
 int MC_STATUS_VAL ; 
 int /*<<< orphan*/  MSR_MCG_CAP ; 
 int /*<<< orphan*/  MSR_MCG_STATUS ; 
 void* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_id ; 
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  cpu_vendor_id ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  do_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ mca_msr_ops ; 
 void* rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 (int) ; 
 int /*<<< orphan*/  stub4 (int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mca_check_status(int bank, struct mca_record *rec)
{
	uint64_t status;
	u_int p[4];

	status = rdmsr(mca_msr_ops.status(bank));
	if (!(status & MC_STATUS_VAL))
		return (0);

	/* Save exception information. */
	rec->mr_status = status;
	rec->mr_bank = bank;
	rec->mr_addr = 0;
	if (status & MC_STATUS_ADDRV)
		rec->mr_addr = rdmsr(mca_msr_ops.addr(bank));
	rec->mr_misc = 0;
	if (status & MC_STATUS_MISCV)
		rec->mr_misc = rdmsr(mca_msr_ops.misc(bank));
	rec->mr_tsc = rdtsc();
	rec->mr_apic_id = PCPU_GET(apic_id);
	rec->mr_mcg_cap = rdmsr(MSR_MCG_CAP);
	rec->mr_mcg_status = rdmsr(MSR_MCG_STATUS);
	rec->mr_cpu_id = cpu_id;
	rec->mr_cpu_vendor_id = cpu_vendor_id;
	rec->mr_cpu = PCPU_GET(cpuid);

	/*
	 * Clear machine check.  Don't do this for uncorrectable
	 * errors so that the BIOS can see them.
	 */
	if (!(rec->mr_status & (MC_STATUS_PCC | MC_STATUS_UC))) {
		wrmsr(mca_msr_ops.status(bank), 0);
		do_cpuid(0, p);
	}
	return (1);
}