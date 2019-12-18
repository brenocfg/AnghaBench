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
struct kvm_sev_info {int /*<<< orphan*/  regions_list; } ;
struct kvm_enc_region {scalar_t__ addr; scalar_t__ size; } ;
struct kvm {int /*<<< orphan*/  lock; } ;
struct enc_region {scalar_t__ uaddr; scalar_t__ size; int /*<<< orphan*/  list; int /*<<< orphan*/  npages; int /*<<< orphan*/  pages; } ;
struct TYPE_2__ {struct kvm_sev_info sev_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTTY ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  kfree (struct enc_region*) ; 
 struct enc_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sev_clflush_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev_guest (struct kvm*) ; 
 int /*<<< orphan*/  sev_pin_memory (struct kvm*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* to_kvm_svm (struct kvm*) ; 

__attribute__((used)) static int svm_register_enc_region(struct kvm *kvm,
				   struct kvm_enc_region *range)
{
	struct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	struct enc_region *region;
	int ret = 0;

	if (!sev_guest(kvm))
		return -ENOTTY;

	if (range->addr > ULONG_MAX || range->size > ULONG_MAX)
		return -EINVAL;

	region = kzalloc(sizeof(*region), GFP_KERNEL_ACCOUNT);
	if (!region)
		return -ENOMEM;

	region->pages = sev_pin_memory(kvm, range->addr, range->size, &region->npages, 1);
	if (!region->pages) {
		ret = -ENOMEM;
		goto e_free;
	}

	/*
	 * The guest may change the memory encryption attribute from C=0 -> C=1
	 * or vice versa for this memory range. Lets make sure caches are
	 * flushed to ensure that guest data gets written into memory with
	 * correct C-bit.
	 */
	sev_clflush_pages(region->pages, region->npages);

	region->uaddr = range->addr;
	region->size = range->size;

	mutex_lock(&kvm->lock);
	list_add_tail(&region->list, &sev->regions_list);
	mutex_unlock(&kvm->lock);

	return ret;

e_free:
	kfree(region);
	return ret;
}