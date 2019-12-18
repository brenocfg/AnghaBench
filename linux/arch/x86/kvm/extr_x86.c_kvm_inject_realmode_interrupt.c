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
struct x86_emulate_ctxt {int op_bytes; int ad_bytes; int /*<<< orphan*/  eflags; scalar_t__ eip; scalar_t__ _eip; } ;
struct TYPE_2__ {struct x86_emulate_ctxt emulate_ctxt; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_TRIPLE_FAULT ; 
 int X86EMUL_CONTINUE ; 
 int emulate_int_real (struct x86_emulate_ctxt*,int) ; 
 int /*<<< orphan*/  init_emulate_ctxt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  kvm_set_rflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_inject_realmode_interrupt(struct kvm_vcpu *vcpu, int irq, int inc_eip)
{
	struct x86_emulate_ctxt *ctxt = &vcpu->arch.emulate_ctxt;
	int ret;

	init_emulate_ctxt(vcpu);

	ctxt->op_bytes = 2;
	ctxt->ad_bytes = 2;
	ctxt->_eip = ctxt->eip + inc_eip;
	ret = emulate_int_real(ctxt, irq);

	if (ret != X86EMUL_CONTINUE) {
		kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
	} else {
		ctxt->eip = ctxt->_eip;
		kvm_rip_write(vcpu, ctxt->eip);
		kvm_set_rflags(vcpu, ctxt->eflags);
	}
}