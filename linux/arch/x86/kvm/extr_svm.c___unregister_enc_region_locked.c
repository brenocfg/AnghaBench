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
struct kvm {int dummy; } ;
struct enc_region {int /*<<< orphan*/  list; int /*<<< orphan*/  npages; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct enc_region*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sev_clflush_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev_unpin_memory (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __unregister_enc_region_locked(struct kvm *kvm,
					   struct enc_region *region)
{
	/*
	 * The guest may change the memory encryption attribute from C=0 -> C=1
	 * or vice versa for this memory range. Lets make sure caches are
	 * flushed to ensure that guest data gets written into memory with
	 * correct C-bit.
	 */
	sev_clflush_pages(region->pages, region->npages);

	sev_unpin_memory(kvm, region->pages, region->npages);
	list_del(&region->list);
	kfree(region);
}