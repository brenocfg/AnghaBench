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
struct kvm_enable_cap {int cap; unsigned long* args; scalar_t__ flags; } ;
struct TYPE_4__ {TYPE_1__* kvm_ops; int /*<<< orphan*/  enabled_hcalls; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_3__ {int (* set_smt_mode ) (struct kvm*,unsigned long,unsigned long) ;int (* enable_nested ) (struct kvm*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_CAP_PPC_ENABLE_HCALL 130 
#define  KVM_CAP_PPC_NESTED_HV 129 
#define  KVM_CAP_PPC_SMT 128 
 unsigned long MAX_HCALL_OPCODE ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_kvmppc_hv_enabled (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_book3s_hcall_implemented (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int stub1 (struct kvm*,unsigned long,unsigned long) ; 
 int stub2 (struct kvm*) ; 

int kvm_vm_ioctl_enable_cap(struct kvm *kvm,
			    struct kvm_enable_cap *cap)
{
	int r;

	if (cap->flags)
		return -EINVAL;

	switch (cap->cap) {
#ifdef CONFIG_KVM_BOOK3S_64_HANDLER
	case KVM_CAP_PPC_ENABLE_HCALL: {
		unsigned long hcall = cap->args[0];

		r = -EINVAL;
		if (hcall > MAX_HCALL_OPCODE || (hcall & 3) ||
		    cap->args[1] > 1)
			break;
		if (!kvmppc_book3s_hcall_implemented(kvm, hcall))
			break;
		if (cap->args[1])
			set_bit(hcall / 4, kvm->arch.enabled_hcalls);
		else
			clear_bit(hcall / 4, kvm->arch.enabled_hcalls);
		r = 0;
		break;
	}
	case KVM_CAP_PPC_SMT: {
		unsigned long mode = cap->args[0];
		unsigned long flags = cap->args[1];

		r = -EINVAL;
		if (kvm->arch.kvm_ops->set_smt_mode)
			r = kvm->arch.kvm_ops->set_smt_mode(kvm, mode, flags);
		break;
	}

	case KVM_CAP_PPC_NESTED_HV:
		r = -EINVAL;
		if (!is_kvmppc_hv_enabled(kvm) ||
		    !kvm->arch.kvm_ops->enable_nested)
			break;
		r = kvm->arch.kvm_ops->enable_nested(kvm);
		break;
#endif
	default:
		r = -EINVAL;
		break;
	}

	return r;
}