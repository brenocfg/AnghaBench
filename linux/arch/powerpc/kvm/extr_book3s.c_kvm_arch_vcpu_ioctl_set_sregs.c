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
struct kvm_vcpu {TYPE_3__* kvm; } ;
struct kvm_sregs {int dummy; } ;
struct TYPE_5__ {TYPE_1__* kvm_ops; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;
struct TYPE_4__ {int (* set_sregs ) (struct kvm_vcpu*,struct kvm_sregs*) ;} ;

/* Variables and functions */
 int stub1 (struct kvm_vcpu*,struct kvm_sregs*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu,
				  struct kvm_sregs *sregs)
{
	int ret;

	vcpu_load(vcpu);
	ret = vcpu->kvm->arch.kvm_ops->set_sregs(vcpu, sregs);
	vcpu_put(vcpu);

	return ret;
}