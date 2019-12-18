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
struct vcpu_vmx {TYPE_1__* loaded_vmcs; int /*<<< orphan*/  req_immediate_exit; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hv_timer_soft_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_lapic_expired_hv_timer (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_preemption_timer(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (!vmx->req_immediate_exit &&
	    !unlikely(vmx->loaded_vmcs->hv_timer_soft_disabled))
		kvm_lapic_expired_hv_timer(vcpu);

	return 1;
}