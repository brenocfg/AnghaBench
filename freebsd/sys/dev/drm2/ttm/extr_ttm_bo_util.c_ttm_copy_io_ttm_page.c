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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct ttm_tt {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 void* pmap_mapdev_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_copy_io_ttm_page(struct ttm_tt *ttm, void *src,
				unsigned long page,
				vm_memattr_t prot)
{
	vm_page_t d = ttm->pages[page];
	void *dst;

	if (!d)
		return -ENOMEM;

	src = (void *)((unsigned long)src + (page << PAGE_SHIFT));

	/* XXXKIB can't sleep ? */
	dst = pmap_mapdev_attr(VM_PAGE_TO_PHYS(d), PAGE_SIZE, prot);
	if (!dst)
		return -ENOMEM;

	memcpy(dst, src, PAGE_SIZE);

	pmap_unmapdev((vm_offset_t)dst, PAGE_SIZE);

	return 0;
}