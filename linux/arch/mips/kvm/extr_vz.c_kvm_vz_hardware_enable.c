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
typedef  unsigned long long u64 ;
struct TYPE_3__ {unsigned int tlbsize; } ;
struct TYPE_4__ {unsigned int tlbsize; unsigned int tlbsizevtlb; int guestid_mask; int guestid_cache; TYPE_1__ guest; } ;

/* Variables and functions */
#define  CPU_CAVIUM_OCTEON3 128 
 unsigned long long CVMCTL_IPPCI ; 
 unsigned long long CVMCTL_IPPCI_SHIFT ; 
 unsigned long long CVMCTL_IPTI ; 
 unsigned long long CVMCTL_IPTI_SHIFT ; 
 unsigned long long CVMVMCONF_DGHT ; 
 unsigned long long CVMVMCONF_MMUSIZEM1 ; 
 unsigned long long CVMVMCONF_MMUSIZEM1_S ; 
 unsigned long long CVMVMCONF_RMMUSIZEM1 ; 
 int EINVAL ; 
 int GUESTID_FIRST_VERSION ; 
 int GUESTID_MASK ; 
 int GUESTID_VERSION_MASK ; 
 int /*<<< orphan*/  MIPS_GCTL0EXT_CGI ; 
 int MIPS_GCTL0_AT_GUEST ; 
 int MIPS_GCTL0_AT_SHIFT ; 
 int MIPS_GCTL0_CF ; 
 int MIPS_GCTL0_CG ; 
 int MIPS_GCTL0_CP0 ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  clear_c0_guestctl2 (int) ; 
 int /*<<< orphan*/  cmpxchg (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ cpu_has_guestctl0ext ; 
 scalar_t__ cpu_has_guestctl2 ; 
 scalar_t__ cpu_has_guestid ; 
 TYPE_2__ current_cpu_data ; 
 int current_cpu_type () ; 
 unsigned int kvm_vz_guest_vtlb_size ; 
 int /*<<< orphan*/  kvm_vz_local_flush_guesttlb_all () ; 
 int /*<<< orphan*/  kvm_vz_local_flush_roottlb_all_guests () ; 
 unsigned int kvm_vz_resize_guest_vtlb (unsigned int) ; 
 int /*<<< orphan*/  num_wired_entries () ; 
 unsigned long long read_c0_cvmvmconfig () ; 
 unsigned long long read_gc0_cvmctl () ; 
 int /*<<< orphan*/  set_c0_guestctl0ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_cvmvmconfig (unsigned long long) ; 
 int /*<<< orphan*/  write_c0_guestctl0 (int) ; 
 int /*<<< orphan*/  write_c0_guestctl1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_gc0_cvmctl (unsigned long long) ; 

__attribute__((used)) static int kvm_vz_hardware_enable(void)
{
	unsigned int mmu_size, guest_mmu_size, ftlb_size;
	u64 guest_cvmctl, cvmvmconfig;

	switch (current_cpu_type()) {
	case CPU_CAVIUM_OCTEON3:
		/* Set up guest timer/perfcount IRQ lines */
		guest_cvmctl = read_gc0_cvmctl();
		guest_cvmctl &= ~CVMCTL_IPTI;
		guest_cvmctl |= 7ull << CVMCTL_IPTI_SHIFT;
		guest_cvmctl &= ~CVMCTL_IPPCI;
		guest_cvmctl |= 6ull << CVMCTL_IPPCI_SHIFT;
		write_gc0_cvmctl(guest_cvmctl);

		cvmvmconfig = read_c0_cvmvmconfig();
		/* No I/O hole translation. */
		cvmvmconfig |= CVMVMCONF_DGHT;
		/* Halve the root MMU size */
		mmu_size = ((cvmvmconfig & CVMVMCONF_MMUSIZEM1)
			    >> CVMVMCONF_MMUSIZEM1_S) + 1;
		guest_mmu_size = mmu_size / 2;
		mmu_size -= guest_mmu_size;
		cvmvmconfig &= ~CVMVMCONF_RMMUSIZEM1;
		cvmvmconfig |= mmu_size - 1;
		write_c0_cvmvmconfig(cvmvmconfig);

		/* Update our records */
		current_cpu_data.tlbsize = mmu_size;
		current_cpu_data.tlbsizevtlb = mmu_size;
		current_cpu_data.guest.tlbsize = guest_mmu_size;

		/* Flush moved entries in new (guest) context */
		kvm_vz_local_flush_guesttlb_all();
		break;
	default:
		/*
		 * ImgTec cores tend to use a shared root/guest TLB. To avoid
		 * overlap of root wired and guest entries, the guest TLB may
		 * need resizing.
		 */
		mmu_size = current_cpu_data.tlbsizevtlb;
		ftlb_size = current_cpu_data.tlbsize - mmu_size;

		/* Try switching to maximum guest VTLB size for flush */
		guest_mmu_size = kvm_vz_resize_guest_vtlb(mmu_size);
		current_cpu_data.guest.tlbsize = guest_mmu_size + ftlb_size;
		kvm_vz_local_flush_guesttlb_all();

		/*
		 * Reduce to make space for root wired entries and at least 2
		 * root non-wired entries. This does assume that long-term wired
		 * entries won't be added later.
		 */
		guest_mmu_size = mmu_size - num_wired_entries() - 2;
		guest_mmu_size = kvm_vz_resize_guest_vtlb(guest_mmu_size);
		current_cpu_data.guest.tlbsize = guest_mmu_size + ftlb_size;

		/*
		 * Write the VTLB size, but if another CPU has already written,
		 * check it matches or we won't provide a consistent view to the
		 * guest. If this ever happens it suggests an asymmetric number
		 * of wired entries.
		 */
		if (cmpxchg(&kvm_vz_guest_vtlb_size, 0, guest_mmu_size) &&
		    WARN(guest_mmu_size != kvm_vz_guest_vtlb_size,
			 "Available guest VTLB size mismatch"))
			return -EINVAL;
		break;
	}

	/*
	 * Enable virtualization features granting guest direct control of
	 * certain features:
	 * CP0=1:	Guest coprocessor 0 context.
	 * AT=Guest:	Guest MMU.
	 * CG=1:	Hit (virtual address) CACHE operations (optional).
	 * CF=1:	Guest Config registers.
	 * CGI=1:	Indexed flush CACHE operations (optional).
	 */
	write_c0_guestctl0(MIPS_GCTL0_CP0 |
			   (MIPS_GCTL0_AT_GUEST << MIPS_GCTL0_AT_SHIFT) |
			   MIPS_GCTL0_CG | MIPS_GCTL0_CF);
	if (cpu_has_guestctl0ext)
		set_c0_guestctl0ext(MIPS_GCTL0EXT_CGI);

	if (cpu_has_guestid) {
		write_c0_guestctl1(0);
		kvm_vz_local_flush_roottlb_all_guests();

		GUESTID_MASK = current_cpu_data.guestid_mask;
		GUESTID_FIRST_VERSION = GUESTID_MASK + 1;
		GUESTID_VERSION_MASK = ~GUESTID_MASK;

		current_cpu_data.guestid_cache = GUESTID_FIRST_VERSION;
	}

	/* clear any pending injected virtual guest interrupts */
	if (cpu_has_guestctl2)
		clear_c0_guestctl2(0x3f << 10);

	return 0;
}