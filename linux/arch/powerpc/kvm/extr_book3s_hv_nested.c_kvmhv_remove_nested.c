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
struct kvm_nested_guest {int l1_lpid; long refcnt; struct kvm* l1_host; } ;
struct TYPE_2__ {int max_nested_lpid; struct kvm_nested_guest** nested_guests; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmhv_release_nested (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmhv_remove_nested(struct kvm_nested_guest *gp)
{
	struct kvm *kvm = gp->l1_host;
	int lpid = gp->l1_lpid;
	long ref;

	spin_lock(&kvm->mmu_lock);
	if (gp == kvm->arch.nested_guests[lpid]) {
		kvm->arch.nested_guests[lpid] = NULL;
		if (lpid == kvm->arch.max_nested_lpid) {
			while (--lpid >= 0 && !kvm->arch.nested_guests[lpid])
				;
			kvm->arch.max_nested_lpid = lpid;
		}
		--gp->refcnt;
	}
	ref = gp->refcnt;
	spin_unlock(&kvm->mmu_lock);
	if (ref == 0)
		kvmhv_release_nested(gp);
}