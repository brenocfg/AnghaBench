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
struct kvm_mmu_memory_cache {int nobjs; void** objects; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmu_topup_memory_cache_page(struct kvm_mmu_memory_cache *cache,
				       int min)
{
	void *page;

	if (cache->nobjs >= min)
		return 0;
	while (cache->nobjs < ARRAY_SIZE(cache->objects)) {
		page = (void *)__get_free_page(GFP_KERNEL_ACCOUNT);
		if (!page)
			return cache->nobjs >= min ? 0 : -ENOMEM;
		cache->objects[cache->nobjs++] = page;
	}
	return 0;
}