#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  tlbsize; } ;
struct TYPE_4__ {unsigned int tlbsize; unsigned int tlbsizevtlb; TYPE_1__ guest; } ;

/* Variables and functions */
#define  CPU_CAVIUM_OCTEON3 128 
 unsigned int CVMVMCONF_MMUSIZEM1 ; 
 unsigned int CVMVMCONF_MMUSIZEM1_S ; 
 unsigned int CVMVMCONF_RMMUSIZEM1 ; 
 scalar_t__ cpu_has_guestid ; 
 TYPE_2__ current_cpu_data ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  kvm_vz_local_flush_guesttlb_all () ; 
 int /*<<< orphan*/  kvm_vz_local_flush_roottlb_all_guests () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 unsigned int read_c0_cvmvmconfig () ; 
 int /*<<< orphan*/  write_c0_cvmvmconfig (unsigned int) ; 
 int /*<<< orphan*/  write_c0_guestctl1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vz_hardware_disable(void)
{
	u64 cvmvmconfig;
	unsigned int mmu_size;

	/* Flush any remaining guest TLB entries */
	kvm_vz_local_flush_guesttlb_all();

	switch (current_cpu_type()) {
	case CPU_CAVIUM_OCTEON3:
		/*
		 * Allocate whole TLB for root. Existing guest TLB entries will
		 * change ownership to the root TLB. We should be safe though as
		 * they've already been flushed above while in guest TLB.
		 */
		cvmvmconfig = read_c0_cvmvmconfig();
		mmu_size = ((cvmvmconfig & CVMVMCONF_MMUSIZEM1)
			    >> CVMVMCONF_MMUSIZEM1_S) + 1;
		cvmvmconfig &= ~CVMVMCONF_RMMUSIZEM1;
		cvmvmconfig |= mmu_size - 1;
		write_c0_cvmvmconfig(cvmvmconfig);

		/* Update our records */
		current_cpu_data.tlbsize = mmu_size;
		current_cpu_data.tlbsizevtlb = mmu_size;
		current_cpu_data.guest.tlbsize = 0;

		/* Flush moved entries in new (root) context */
		local_flush_tlb_all();
		break;
	}

	if (cpu_has_guestid) {
		write_c0_guestctl1(0);
		kvm_vz_local_flush_roottlb_all_guests();
	}
}