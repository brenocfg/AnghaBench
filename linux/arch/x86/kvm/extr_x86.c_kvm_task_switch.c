#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ctxt {int /*<<< orphan*/  eflags; int /*<<< orphan*/  eip; } ;
struct TYPE_6__ {struct x86_emulate_ctxt emulate_ctxt; } ;
struct kvm_vcpu {TYPE_2__* run; TYPE_3__ arch; } ;
struct TYPE_4__ {scalar_t__ ndata; int /*<<< orphan*/  suberror; } ;
struct TYPE_5__ {TYPE_1__ internal; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  KVM_INTERNAL_ERROR_EMULATION ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int emulator_task_switch (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_emulate_ctxt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_rflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

int kvm_task_switch(struct kvm_vcpu *vcpu, u16 tss_selector, int idt_index,
		    int reason, bool has_error_code, u32 error_code)
{
	struct x86_emulate_ctxt *ctxt = &vcpu->arch.emulate_ctxt;
	int ret;

	init_emulate_ctxt(vcpu);

	ret = emulator_task_switch(ctxt, tss_selector, idt_index, reason,
				   has_error_code, error_code);
	if (ret) {
		vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->internal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->internal.ndata = 0;
		return 0;
	}

	kvm_rip_write(vcpu, ctxt->eip);
	kvm_set_rflags(vcpu, ctxt->eflags);
	kvm_make_request(KVM_REQ_EVENT, vcpu);
	return 1;
}