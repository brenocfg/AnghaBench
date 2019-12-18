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
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 void* kmem_cache_zalloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmu_topup_memory_cache(struct kvm_mmu_memory_cache *cache,
				  struct kmem_cache *base_cache, int min)
{
	void *obj;

	if (cache->nobjs >= min)
		return 0;
	while (cache->nobjs < ARRAY_SIZE(cache->objects)) {
		obj = kmem_cache_zalloc(base_cache, GFP_KERNEL_ACCOUNT);
		if (!obj)
			return cache->nobjs >= min ? 0 : -ENOMEM;
		cache->objects[cache->nobjs++] = obj;
	}
	return 0;
}