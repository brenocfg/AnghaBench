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
struct TYPE_4__ {int /*<<< orphan*/  halted; } ;
struct TYPE_5__ {scalar_t__ mp_state; TYPE_1__ apf; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* check_nested_events ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 scalar_t__ KVM_MP_STATE_RUNNABLE ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 TYPE_3__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

__attribute__((used)) static inline bool kvm_vcpu_running(struct kvm_vcpu *vcpu)
{
	if (is_guest_mode(vcpu) && kvm_x86_ops->check_nested_events)
		kvm_x86_ops->check_nested_events(vcpu, false);

	return (vcpu->arch.mp_state == KVM_MP_STATE_RUNNABLE &&
		!vcpu->arch.apf.halted);
}