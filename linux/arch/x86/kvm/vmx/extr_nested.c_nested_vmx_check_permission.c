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
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vmxon; } ;
struct TYPE_4__ {TYPE_1__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  UD_VECTOR ; 
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 scalar_t__ vmx_get_cpl (struct kvm_vcpu*) ; 

__attribute__((used)) static int nested_vmx_check_permission(struct kvm_vcpu *vcpu)
{
	if (!to_vmx(vcpu)->nested.vmxon) {
		kvm_queue_exception(vcpu, UD_VECTOR);
		return 0;
	}

	if (vmx_get_cpl(vcpu)) {
		kvm_inject_gp(vcpu, 0);
		return 0;
	}

	return 1;
}