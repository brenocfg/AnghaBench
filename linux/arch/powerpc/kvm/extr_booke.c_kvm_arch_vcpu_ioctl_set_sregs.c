#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pvr; } ;
struct kvm_vcpu {TYPE_4__* kvm; TYPE_1__ arch; } ;
struct kvm_sregs {scalar_t__ pvr; } ;
struct TYPE_6__ {TYPE_3__* kvm_ops; } ;
struct TYPE_8__ {TYPE_2__ arch; } ;
struct TYPE_7__ {int (* set_sregs ) (struct kvm_vcpu*,struct kvm_sregs*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int set_sregs_arch206 (struct kvm_vcpu*,struct kvm_sregs*) ; 
 int set_sregs_base (struct kvm_vcpu*,struct kvm_sregs*) ; 
 int stub1 (struct kvm_vcpu*,struct kvm_sregs*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu,
                                  struct kvm_sregs *sregs)
{
	int ret = -EINVAL;

	vcpu_load(vcpu);
	if (vcpu->arch.pvr != sregs->pvr)
		goto out;

	ret = set_sregs_base(vcpu, sregs);
	if (ret < 0)
		goto out;

	ret = set_sregs_arch206(vcpu, sregs);
	if (ret < 0)
		goto out;

	ret = vcpu->kvm->arch.kvm_ops->set_sregs(vcpu, sregs);

out:
	vcpu_put(vcpu);
	return ret;
}