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
struct kvm_nested_guest {int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int l1_ptcr; int max_nested_lpid; struct kvm_nested_guest** nested_guests; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int KVM_MAX_NESTED_GUESTS ; 
 int PRTS_MASK ; 
 struct kvm_nested_guest* kvmhv_alloc_nested (struct kvm*,int) ; 
 int /*<<< orphan*/  kvmhv_release_nested (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct kvm_nested_guest *kvmhv_get_nested(struct kvm *kvm, int l1_lpid,
					  bool create)
{
	struct kvm_nested_guest *gp, *newgp;

	if (l1_lpid >= KVM_MAX_NESTED_GUESTS ||
	    l1_lpid >= (1ul << ((kvm->arch.l1_ptcr & PRTS_MASK) + 12 - 4)))
		return NULL;

	spin_lock(&kvm->mmu_lock);
	gp = kvm->arch.nested_guests[l1_lpid];
	if (gp)
		++gp->refcnt;
	spin_unlock(&kvm->mmu_lock);

	if (gp || !create)
		return gp;

	newgp = kvmhv_alloc_nested(kvm, l1_lpid);
	if (!newgp)
		return NULL;
	spin_lock(&kvm->mmu_lock);
	if (kvm->arch.nested_guests[l1_lpid]) {
		/* someone else beat us to it */
		gp = kvm->arch.nested_guests[l1_lpid];
	} else {
		kvm->arch.nested_guests[l1_lpid] = newgp;
		++newgp->refcnt;
		gp = newgp;
		newgp = NULL;
		if (l1_lpid > kvm->arch.max_nested_lpid)
			kvm->arch.max_nested_lpid = l1_lpid;
	}
	++gp->refcnt;
	spin_unlock(&kvm->mmu_lock);

	if (newgp)
		kvmhv_release_nested(newgp);

	return gp;
}