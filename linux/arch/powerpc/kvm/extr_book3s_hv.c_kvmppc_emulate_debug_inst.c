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
typedef  scalar_t__ u32 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct kvm_run {TYPE_2__ debug; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 scalar_t__ EMULATE_DONE ; 
 int /*<<< orphan*/  INST_GENERIC ; 
 scalar_t__ KVMPPC_INST_SW_BREAKPOINT ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int RESUME_GUEST ; 
 int RESUME_HOST ; 
 int /*<<< orphan*/  SRR1_PROGILL ; 
 int /*<<< orphan*/  kvmppc_core_queue_program (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvmppc_get_last_inst (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  kvmppc_get_pc (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvmppc_emulate_debug_inst(struct kvm_run *run,
					struct kvm_vcpu *vcpu)
{
	u32 last_inst;

	if (kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst) !=
					EMULATE_DONE) {
		/*
		 * Fetch failed, so return to guest and
		 * try executing it again.
		 */
		return RESUME_GUEST;
	}

	if (last_inst == KVMPPC_INST_SW_BREAKPOINT) {
		run->exit_reason = KVM_EXIT_DEBUG;
		run->debug.arch.address = kvmppc_get_pc(vcpu);
		return RESUME_HOST;
	} else {
		kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
		return RESUME_GUEST;
	}
}