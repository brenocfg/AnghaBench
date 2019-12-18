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
typedef  scalar_t__ u32 ;
struct kvmppc_vcore {unsigned long lpcr; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {unsigned long lpcr; scalar_t__ online_vcores; struct kvmppc_vcore** vcores; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 long KVM_MAX_VCORES ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvmppc_update_lpcr(struct kvm *kvm, unsigned long lpcr, unsigned long mask)
{
	long int i;
	u32 cores_done = 0;

	if ((kvm->arch.lpcr & mask) == lpcr)
		return;

	kvm->arch.lpcr = (kvm->arch.lpcr & ~mask) | lpcr;

	for (i = 0; i < KVM_MAX_VCORES; ++i) {
		struct kvmppc_vcore *vc = kvm->arch.vcores[i];
		if (!vc)
			continue;
		spin_lock(&vc->lock);
		vc->lpcr = (vc->lpcr & ~mask) | lpcr;
		spin_unlock(&vc->lock);
		if (++cores_done >= kvm->arch.online_vcores)
			break;
	}
}