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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {unsigned long pc; struct kvm_mips_tlb* guest_tlb; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mips_tlb {int /*<<< orphan*/ * tlb_lo; int /*<<< orphan*/  tlb_hi; int /*<<< orphan*/  tlb_mask; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int /*<<< orphan*/  KVM_MIPS_GUEST_TLB_SIZE ; 
 int /*<<< orphan*/  kvm_debug (char*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mips_invalidate_guest_tlb (struct kvm_vcpu*,struct kvm_mips_tlb*) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_entryhi (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_entrylo0 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_entrylo1 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_pagemask (struct mips_coproc*) ; 
 int prandom_u32_max (int /*<<< orphan*/ ) ; 

enum emulation_result kvm_mips_emul_tlbwr(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	struct kvm_mips_tlb *tlb = NULL;
	unsigned long pc = vcpu->arch.pc;
	int index;

	index = prandom_u32_max(KVM_MIPS_GUEST_TLB_SIZE);
	tlb = &vcpu->arch.guest_tlb[index];

	kvm_mips_invalidate_guest_tlb(vcpu, tlb);

	tlb->tlb_mask = kvm_read_c0_guest_pagemask(cop0);
	tlb->tlb_hi = kvm_read_c0_guest_entryhi(cop0);
	tlb->tlb_lo[0] = kvm_read_c0_guest_entrylo0(cop0);
	tlb->tlb_lo[1] = kvm_read_c0_guest_entrylo1(cop0);

	kvm_debug("[%#lx] COP0_TLBWR[%d] (entryhi: %#lx, entrylo0: %#lx entrylo1: %#lx)\n",
		  pc, index, kvm_read_c0_guest_entryhi(cop0),
		  kvm_read_c0_guest_entrylo0(cop0),
		  kvm_read_c0_guest_entrylo1(cop0));

	return EMULATE_DONE;
}