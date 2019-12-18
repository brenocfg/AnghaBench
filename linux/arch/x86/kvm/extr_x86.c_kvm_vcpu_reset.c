#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mpx_bndreg_state {int dummy; } ;
struct mpx_bndcsr {int dummy; } ;
struct TYPE_10__ {int halted; scalar_t__ msr_val; } ;
struct TYPE_9__ {scalar_t__ msr_val; } ;
struct TYPE_8__ {int pending; } ;
struct TYPE_13__ {int nmi_injected; void* db; int smbase; void* regs; scalar_t__ ia32_xss; int /*<<< orphan*/  regs_dirty; int /*<<< orphan*/  regs_avail; int /*<<< orphan*/  xcr0; scalar_t__ msr_misc_features_enables; TYPE_5__* guest_fpu; TYPE_3__ apf; TYPE_2__ st; scalar_t__ cr2; int /*<<< orphan*/  dr7; int /*<<< orphan*/  dr6; TYPE_1__ exception; scalar_t__ nmi_pending; int /*<<< orphan*/  nmi_queued; scalar_t__ smi_count; scalar_t__ smi_pending; scalar_t__ hflags; } ;
struct kvm_vcpu {TYPE_6__ arch; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* vcpu_reset ) (struct kvm_vcpu*,int) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  xsave; } ;
struct TYPE_12__ {TYPE_4__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR6_INIT ; 
 int /*<<< orphan*/  DR7_FIXED_1 ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  XFEATURE_BNDCSR ; 
 int /*<<< orphan*/  XFEATURE_BNDREGS ; 
 int /*<<< orphan*/  XFEATURE_MASK_FP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* get_xsave_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_async_pf_hash_reset (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_clear_async_pf_completion_queue (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_clear_interrupt_queue (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_lapic_reset (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_load_guest_fpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ kvm_mpx_supported () ; 
 int /*<<< orphan*/  kvm_pmu_reset (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_put_guest_fpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr0123 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr6 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr7 (struct kvm_vcpu*) ; 
 TYPE_7__* kvm_x86_ops ; 
 int /*<<< orphan*/  kvmclock_reset (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

void kvm_vcpu_reset(struct kvm_vcpu *vcpu, bool init_event)
{
	kvm_lapic_reset(vcpu, init_event);

	vcpu->arch.hflags = 0;

	vcpu->arch.smi_pending = 0;
	vcpu->arch.smi_count = 0;
	atomic_set(&vcpu->arch.nmi_queued, 0);
	vcpu->arch.nmi_pending = 0;
	vcpu->arch.nmi_injected = false;
	kvm_clear_interrupt_queue(vcpu);
	kvm_clear_exception_queue(vcpu);
	vcpu->arch.exception.pending = false;

	memset(vcpu->arch.db, 0, sizeof(vcpu->arch.db));
	kvm_update_dr0123(vcpu);
	vcpu->arch.dr6 = DR6_INIT;
	kvm_update_dr6(vcpu);
	vcpu->arch.dr7 = DR7_FIXED_1;
	kvm_update_dr7(vcpu);

	vcpu->arch.cr2 = 0;

	kvm_make_request(KVM_REQ_EVENT, vcpu);
	vcpu->arch.apf.msr_val = 0;
	vcpu->arch.st.msr_val = 0;

	kvmclock_reset(vcpu);

	kvm_clear_async_pf_completion_queue(vcpu);
	kvm_async_pf_hash_reset(vcpu);
	vcpu->arch.apf.halted = false;

	if (kvm_mpx_supported()) {
		void *mpx_state_buffer;

		/*
		 * To avoid have the INIT path from kvm_apic_has_events() that be
		 * called with loaded FPU and does not let userspace fix the state.
		 */
		if (init_event)
			kvm_put_guest_fpu(vcpu);
		mpx_state_buffer = get_xsave_addr(&vcpu->arch.guest_fpu->state.xsave,
					XFEATURE_BNDREGS);
		if (mpx_state_buffer)
			memset(mpx_state_buffer, 0, sizeof(struct mpx_bndreg_state));
		mpx_state_buffer = get_xsave_addr(&vcpu->arch.guest_fpu->state.xsave,
					XFEATURE_BNDCSR);
		if (mpx_state_buffer)
			memset(mpx_state_buffer, 0, sizeof(struct mpx_bndcsr));
		if (init_event)
			kvm_load_guest_fpu(vcpu);
	}

	if (!init_event) {
		kvm_pmu_reset(vcpu);
		vcpu->arch.smbase = 0x30000;

		vcpu->arch.msr_misc_features_enables = 0;

		vcpu->arch.xcr0 = XFEATURE_MASK_FP;
	}

	memset(vcpu->arch.regs, 0, sizeof(vcpu->arch.regs));
	vcpu->arch.regs_avail = ~0;
	vcpu->arch.regs_dirty = ~0;

	vcpu->arch.ia32_xss = 0;

	kvm_x86_ops->vcpu_reset(vcpu, init_event);
}