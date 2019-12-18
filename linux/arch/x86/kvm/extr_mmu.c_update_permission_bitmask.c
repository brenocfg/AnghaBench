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
typedef  int u8 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {int* permissions; int /*<<< orphan*/  nx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_EXEC_MASK ; 
 int /*<<< orphan*/  ACC_USER_MASK ; 
 int /*<<< orphan*/  ACC_WRITE_MASK ; 
 unsigned int ARRAY_SIZE (int*) ; 
 int BYTE_MASK (int /*<<< orphan*/ ) ; 
 unsigned int PFERR_FETCH_MASK ; 
 unsigned int PFERR_RSVD_MASK ; 
 unsigned int PFERR_USER_MASK ; 
 unsigned int PFERR_WRITE_MASK ; 
 int /*<<< orphan*/  X86_CR4_SMAP ; 
 int /*<<< orphan*/  X86_CR4_SMEP ; 
 int is_write_protection (struct kvm_vcpu*) ; 
 scalar_t__ kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_permission_bitmask(struct kvm_vcpu *vcpu,
				      struct kvm_mmu *mmu, bool ept)
{
	unsigned byte;

	const u8 x = BYTE_MASK(ACC_EXEC_MASK);
	const u8 w = BYTE_MASK(ACC_WRITE_MASK);
	const u8 u = BYTE_MASK(ACC_USER_MASK);

	bool cr4_smep = kvm_read_cr4_bits(vcpu, X86_CR4_SMEP) != 0;
	bool cr4_smap = kvm_read_cr4_bits(vcpu, X86_CR4_SMAP) != 0;
	bool cr0_wp = is_write_protection(vcpu);

	for (byte = 0; byte < ARRAY_SIZE(mmu->permissions); ++byte) {
		unsigned pfec = byte << 1;

		/*
		 * Each "*f" variable has a 1 bit for each UWX value
		 * that causes a fault with the given PFEC.
		 */

		/* Faults from writes to non-writable pages */
		u8 wf = (pfec & PFERR_WRITE_MASK) ? (u8)~w : 0;
		/* Faults from user mode accesses to supervisor pages */
		u8 uf = (pfec & PFERR_USER_MASK) ? (u8)~u : 0;
		/* Faults from fetches of non-executable pages*/
		u8 ff = (pfec & PFERR_FETCH_MASK) ? (u8)~x : 0;
		/* Faults from kernel mode fetches of user pages */
		u8 smepf = 0;
		/* Faults from kernel mode accesses of user pages */
		u8 smapf = 0;

		if (!ept) {
			/* Faults from kernel mode accesses to user pages */
			u8 kf = (pfec & PFERR_USER_MASK) ? 0 : u;

			/* Not really needed: !nx will cause pte.nx to fault */
			if (!mmu->nx)
				ff = 0;

			/* Allow supervisor writes if !cr0.wp */
			if (!cr0_wp)
				wf = (pfec & PFERR_USER_MASK) ? wf : 0;

			/* Disallow supervisor fetches of user code if cr4.smep */
			if (cr4_smep)
				smepf = (pfec & PFERR_FETCH_MASK) ? kf : 0;

			/*
			 * SMAP:kernel-mode data accesses from user-mode
			 * mappings should fault. A fault is considered
			 * as a SMAP violation if all of the following
			 * conditions are true:
			 *   - X86_CR4_SMAP is set in CR4
			 *   - A user page is accessed
			 *   - The access is not a fetch
			 *   - Page fault in kernel mode
			 *   - if CPL = 3 or X86_EFLAGS_AC is clear
			 *
			 * Here, we cover the first three conditions.
			 * The fourth is computed dynamically in permission_fault();
			 * PFERR_RSVD_MASK bit will be set in PFEC if the access is
			 * *not* subject to SMAP restrictions.
			 */
			if (cr4_smap)
				smapf = (pfec & (PFERR_RSVD_MASK|PFERR_FETCH_MASK)) ? 0 : kf;
		}

		mmu->permissions[byte] = ff | uf | wf | smepf | smapf;
	}
}