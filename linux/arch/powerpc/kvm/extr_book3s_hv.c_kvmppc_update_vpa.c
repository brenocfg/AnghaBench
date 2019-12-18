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
struct kvmppc_vpa {unsigned long next_gpa; unsigned long len; void* pinned_addr; unsigned long gpa; int dirty; void* pinned_end; scalar_t__ update_pending; } ;
struct TYPE_2__ {int /*<<< orphan*/  vpa_update_lock; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 void* kvmppc_pin_guest_page (struct kvm*,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  kvmppc_unpin_guest_page (struct kvm*,void*,unsigned long,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmppc_update_vpa(struct kvm_vcpu *vcpu, struct kvmppc_vpa *vpap)
{
	struct kvm *kvm = vcpu->kvm;
	void *va;
	unsigned long nb;
	unsigned long gpa;

	/*
	 * We need to pin the page pointed to by vpap->next_gpa,
	 * but we can't call kvmppc_pin_guest_page under the lock
	 * as it does get_user_pages() and down_read().  So we
	 * have to drop the lock, pin the page, then get the lock
	 * again and check that a new area didn't get registered
	 * in the meantime.
	 */
	for (;;) {
		gpa = vpap->next_gpa;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		va = NULL;
		nb = 0;
		if (gpa)
			va = kvmppc_pin_guest_page(kvm, gpa, &nb);
		spin_lock(&vcpu->arch.vpa_update_lock);
		if (gpa == vpap->next_gpa)
			break;
		/* sigh... unpin that one and try again */
		if (va)
			kvmppc_unpin_guest_page(kvm, va, gpa, false);
	}

	vpap->update_pending = 0;
	if (va && nb < vpap->len) {
		/*
		 * If it's now too short, it must be that userspace
		 * has changed the mappings underlying guest memory,
		 * so unregister the region.
		 */
		kvmppc_unpin_guest_page(kvm, va, gpa, false);
		va = NULL;
	}
	if (vpap->pinned_addr)
		kvmppc_unpin_guest_page(kvm, vpap->pinned_addr, vpap->gpa,
					vpap->dirty);
	vpap->gpa = gpa;
	vpap->pinned_addr = va;
	vpap->dirty = false;
	if (va)
		vpap->pinned_end = va + vpap->len;
}