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
struct TYPE_5__ {int /*<<< orphan*/  mp_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  halt_exits; } ;
struct kvm_vcpu {TYPE_3__* run; TYPE_2__ arch; TYPE_1__ stat; } ;
struct TYPE_6__ {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_HLT ; 
 int /*<<< orphan*/  KVM_MP_STATE_HALTED ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 

int kvm_vcpu_halt(struct kvm_vcpu *vcpu)
{
	++vcpu->stat.halt_exits;
	if (lapic_in_kernel(vcpu)) {
		vcpu->arch.mp_state = KVM_MP_STATE_HALTED;
		return 1;
	} else {
		vcpu->run->exit_reason = KVM_EXIT_HLT;
		return 0;
	}
}