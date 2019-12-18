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
struct sq_mapping {unsigned long addr; unsigned int size; char const* name; unsigned long sq_addr; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long EINVAL ; 
 unsigned long ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long P4SEG_STORE_QUE ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int __sq_remap (struct sq_mapping*,int /*<<< orphan*/ ) ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (unsigned int) ; 
 int /*<<< orphan*/  high_memory ; 
 struct sq_mapping* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sq_mapping*) ; 
 scalar_t__ likely (char const*) ; 
 int /*<<< orphan*/  pr_info (char*,char*,unsigned int,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  sq_bitmap ; 
 int /*<<< orphan*/  sq_cache ; 
 int /*<<< orphan*/  sq_mapping_list_add (struct sq_mapping*) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long virt_to_phys (int /*<<< orphan*/ ) ; 

unsigned long sq_remap(unsigned long phys, unsigned int size,
		       const char *name, pgprot_t prot)
{
	struct sq_mapping *map;
	unsigned long end;
	unsigned int psz;
	int ret, page;

	/* Don't allow wraparound or zero size */
	end = phys + size - 1;
	if (unlikely(!size || end < phys))
		return -EINVAL;
	/* Don't allow anyone to remap normal memory.. */
	if (unlikely(phys < virt_to_phys(high_memory)))
		return -EINVAL;

	phys &= PAGE_MASK;
	size = PAGE_ALIGN(end + 1) - phys;

	map = kmem_cache_alloc(sq_cache, GFP_KERNEL);
	if (unlikely(!map))
		return -ENOMEM;

	map->addr = phys;
	map->size = size;
	map->name = name;

	page = bitmap_find_free_region(sq_bitmap, 0x04000000 >> PAGE_SHIFT,
				       get_order(map->size));
	if (unlikely(page < 0)) {
		ret = -ENOSPC;
		goto out;
	}

	map->sq_addr = P4SEG_STORE_QUE + (page << PAGE_SHIFT);

	ret = __sq_remap(map, prot);
	if (unlikely(ret != 0))
		goto out;

	psz = (size + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	pr_info("sqremap: %15s  [%4d page%s]  va 0x%08lx   pa 0x%08lx\n",
		likely(map->name) ? map->name : "???",
		psz, psz == 1 ? " " : "s",
		map->sq_addr, map->addr);

	sq_mapping_list_add(map);

	return map->sq_addr;

out:
	kmem_cache_free(sq_cache, map);
	return ret;
}