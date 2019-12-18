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
struct TYPE_3__ {int apicv_active; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* refresh_apicv_exec_ctrl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

void kvm_vcpu_deactivate_apicv(struct kvm_vcpu *vcpu)
{
	if (!lapic_in_kernel(vcpu)) {
		WARN_ON_ONCE(vcpu->arch.apicv_active);
		return;
	}
	if (!vcpu->arch.apicv_active)
		return;

	vcpu->arch.apicv_active = false;
	kvm_x86_ops->refresh_apicv_exec_ctrl(vcpu);
}