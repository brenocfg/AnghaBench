#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct msr_data {int host_initiated; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ cr3; scalar_t__ efer; scalar_t__ cr0; int /*<<< orphan*/  mp_state; int /*<<< orphan*/  walk_mmu; int /*<<< orphan*/  regs_avail; int /*<<< orphan*/  cr2; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_3__* kvm; } ;
struct TYPE_12__ {int selector; int base; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; } ;
struct kvm_sregs {scalar_t__ cr3; scalar_t__ efer; scalar_t__ cr0; int cr4; TYPE_6__ cs; TYPE_6__ ldt; TYPE_6__ tr; TYPE_6__ ss; TYPE_6__ gs; TYPE_6__ fs; TYPE_6__ es; TYPE_6__ ds; scalar_t__ interrupt_bitmap; int /*<<< orphan*/  cr8; int /*<<< orphan*/  cr2; TYPE_2__ gdt; TYPE_1__ idt; int /*<<< orphan*/  apic_base; } ;
struct desc_ptr {int /*<<< orphan*/  address; int /*<<< orphan*/  size; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* set_cr4 ) (struct kvm_vcpu*,int) ;int /*<<< orphan*/  (* set_cr0 ) (struct kvm_vcpu*,scalar_t__) ;int /*<<< orphan*/  (* set_efer ) (struct kvm_vcpu*,scalar_t__) ;int /*<<< orphan*/  (* set_gdt ) (struct kvm_vcpu*,struct desc_ptr*) ;int /*<<< orphan*/  (* set_idt ) (struct kvm_vcpu*,struct desc_ptr*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_MP_STATE_RUNNABLE ; 
 int KVM_NR_INTERRUPTS ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  VCPU_EXREG_CR3 ; 
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int /*<<< orphan*/  VCPU_SREG_DS ; 
 int /*<<< orphan*/  VCPU_SREG_ES ; 
 int /*<<< orphan*/  VCPU_SREG_FS ; 
 int /*<<< orphan*/  VCPU_SREG_GS ; 
 int /*<<< orphan*/  VCPU_SREG_LDTR ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 int /*<<< orphan*/  VCPU_SREG_TR ; 
 int X86_CR4_OSXSAVE ; 
 int X86_CR4_PKE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int find_first_bit (unsigned long const*,int) ; 
 scalar_t__ is_pae_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_protmode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_interrupt (struct kvm_vcpu*,int,int) ; 
 scalar_t__ kvm_read_cr0 (struct kvm_vcpu*) ; 
 scalar_t__ kvm_read_cr3 (struct kvm_vcpu*) ; 
 int kvm_read_cr4 (struct kvm_vcpu*) ; 
 int kvm_rip_read (struct kvm_vcpu*) ; 
 scalar_t__ kvm_set_apic_base (struct kvm_vcpu*,struct msr_data*) ; 
 int /*<<< orphan*/  kvm_set_cr8 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_segment (struct kvm_vcpu*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_update_cpuid (struct kvm_vcpu*) ; 
 scalar_t__ kvm_valid_sregs (struct kvm_vcpu*,struct kvm_sregs*) ; 
 scalar_t__ kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 TYPE_5__* kvm_x86_ops ; 
 int /*<<< orphan*/  load_pdptrs (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,struct desc_ptr*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,struct desc_ptr*) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  update_cr8_intercept (struct kvm_vcpu*) ; 

__attribute__((used)) static int __set_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
{
	struct msr_data apic_base_msr;
	int mmu_reset_needed = 0;
	int cpuid_update_needed = 0;
	int pending_vec, max_bits, idx;
	struct desc_ptr dt;
	int ret = -EINVAL;

	if (kvm_valid_sregs(vcpu, sregs))
		goto out;

	apic_base_msr.data = sregs->apic_base;
	apic_base_msr.host_initiated = true;
	if (kvm_set_apic_base(vcpu, &apic_base_msr))
		goto out;

	dt.size = sregs->idt.limit;
	dt.address = sregs->idt.base;
	kvm_x86_ops->set_idt(vcpu, &dt);
	dt.size = sregs->gdt.limit;
	dt.address = sregs->gdt.base;
	kvm_x86_ops->set_gdt(vcpu, &dt);

	vcpu->arch.cr2 = sregs->cr2;
	mmu_reset_needed |= kvm_read_cr3(vcpu) != sregs->cr3;
	vcpu->arch.cr3 = sregs->cr3;
	__set_bit(VCPU_EXREG_CR3, (ulong *)&vcpu->arch.regs_avail);

	kvm_set_cr8(vcpu, sregs->cr8);

	mmu_reset_needed |= vcpu->arch.efer != sregs->efer;
	kvm_x86_ops->set_efer(vcpu, sregs->efer);

	mmu_reset_needed |= kvm_read_cr0(vcpu) != sregs->cr0;
	kvm_x86_ops->set_cr0(vcpu, sregs->cr0);
	vcpu->arch.cr0 = sregs->cr0;

	mmu_reset_needed |= kvm_read_cr4(vcpu) != sregs->cr4;
	cpuid_update_needed |= ((kvm_read_cr4(vcpu) ^ sregs->cr4) &
				(X86_CR4_OSXSAVE | X86_CR4_PKE));
	kvm_x86_ops->set_cr4(vcpu, sregs->cr4);
	if (cpuid_update_needed)
		kvm_update_cpuid(vcpu);

	idx = srcu_read_lock(&vcpu->kvm->srcu);
	if (is_pae_paging(vcpu)) {
		load_pdptrs(vcpu, vcpu->arch.walk_mmu, kvm_read_cr3(vcpu));
		mmu_reset_needed = 1;
	}
	srcu_read_unlock(&vcpu->kvm->srcu, idx);

	if (mmu_reset_needed)
		kvm_mmu_reset_context(vcpu);

	max_bits = KVM_NR_INTERRUPTS;
	pending_vec = find_first_bit(
		(const unsigned long *)sregs->interrupt_bitmap, max_bits);
	if (pending_vec < max_bits) {
		kvm_queue_interrupt(vcpu, pending_vec, false);
		pr_debug("Set back pending irq %d\n", pending_vec);
	}

	kvm_set_segment(vcpu, &sregs->cs, VCPU_SREG_CS);
	kvm_set_segment(vcpu, &sregs->ds, VCPU_SREG_DS);
	kvm_set_segment(vcpu, &sregs->es, VCPU_SREG_ES);
	kvm_set_segment(vcpu, &sregs->fs, VCPU_SREG_FS);
	kvm_set_segment(vcpu, &sregs->gs, VCPU_SREG_GS);
	kvm_set_segment(vcpu, &sregs->ss, VCPU_SREG_SS);

	kvm_set_segment(vcpu, &sregs->tr, VCPU_SREG_TR);
	kvm_set_segment(vcpu, &sregs->ldt, VCPU_SREG_LDTR);

	update_cr8_intercept(vcpu);

	/* Older userspace won't unhalt the vcpu on reset. */
	if (kvm_vcpu_is_bsp(vcpu) && kvm_rip_read(vcpu) == 0xfff0 &&
	    sregs->cs.selector == 0xf000 && sregs->cs.base == 0xffff0000 &&
	    !is_protmode(vcpu))
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	ret = 0;
out:
	return ret;
}