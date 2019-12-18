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
struct page {int dummy; } ;
struct TYPE_2__ {int apic_access_page_done; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ACCESS_PAGE_PRIVATE_MEMSLOT ; 
 int APIC_DEFAULT_PHYS_BASE ; 
 int EFAULT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __x86_set_memory_region (struct kvm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct page* gfn_to_page (struct kvm*,int) ; 
 scalar_t__ is_error_page (struct page*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int alloc_apic_access_page(struct kvm *kvm)
{
	struct page *page;
	int r = 0;

	mutex_lock(&kvm->slots_lock);
	if (kvm->arch.apic_access_page_done)
		goto out;
	r = __x86_set_memory_region(kvm, APIC_ACCESS_PAGE_PRIVATE_MEMSLOT,
				    APIC_DEFAULT_PHYS_BASE, PAGE_SIZE);
	if (r)
		goto out;

	page = gfn_to_page(kvm, APIC_DEFAULT_PHYS_BASE >> PAGE_SHIFT);
	if (is_error_page(page)) {
		r = -EFAULT;
		goto out;
	}

	/*
	 * Do not pin the page in memory, so that memory hot-unplug
	 * is able to migrate it.
	 */
	put_page(page);
	kvm->arch.apic_access_page_done = true;
out:
	mutex_unlock(&kvm->slots_lock);
	return r;
}