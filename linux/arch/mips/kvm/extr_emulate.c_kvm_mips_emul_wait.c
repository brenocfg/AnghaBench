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
struct TYPE_6__ {int wait; int /*<<< orphan*/  pending_exceptions; int /*<<< orphan*/  pc; } ;
struct TYPE_5__ {int /*<<< orphan*/  wait_exits; } ;
struct kvm_vcpu {TYPE_1__* run; TYPE_3__ arch; TYPE_2__ stat; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;
struct TYPE_4__ {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int /*<<< orphan*/  KVM_EXIT_IRQ_WINDOW_OPEN ; 
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 int /*<<< orphan*/  KVM_TRACE_EXIT_WAIT ; 
 scalar_t__ kvm_check_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_clear_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vz_lose_htimer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_exit (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

enum emulation_result kvm_mips_emul_wait(struct kvm_vcpu *vcpu)
{
	kvm_debug("[%#lx] !!!WAIT!!! (%#lx)\n", vcpu->arch.pc,
		  vcpu->arch.pending_exceptions);

	++vcpu->stat.wait_exits;
	trace_kvm_exit(vcpu, KVM_TRACE_EXIT_WAIT);
	if (!vcpu->arch.pending_exceptions) {
		kvm_vz_lose_htimer(vcpu);
		vcpu->arch.wait = 1;
		kvm_vcpu_block(vcpu);

		/*
		 * We we are runnable, then definitely go off to user space to
		 * check if any I/O interrupts are pending.
		 */
		if (kvm_check_request(KVM_REQ_UNHALT, vcpu)) {
			kvm_clear_request(KVM_REQ_UNHALT, vcpu);
			vcpu->run->exit_reason = KVM_EXIT_IRQ_WINDOW_OPEN;
		}
	}

	return EMULATE_DONE;
}