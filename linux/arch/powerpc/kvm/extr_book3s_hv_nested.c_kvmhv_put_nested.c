#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_nested_guest {long refcnt; struct kvm* l1_host; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmhv_release_nested (struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvmhv_put_nested(struct kvm_nested_guest *gp)
{
	struct kvm *kvm = gp->l1_host;
	long ref;

	spin_lock(&kvm->mmu_lock);
	ref = --gp->refcnt;
	spin_unlock(&kvm->mmu_lock);
	if (ref == 0)
		kvmhv_release_nested(gp);
}