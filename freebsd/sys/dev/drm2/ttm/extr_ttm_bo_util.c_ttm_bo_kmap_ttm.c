#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct ttm_tt {scalar_t__ state; int /*<<< orphan*/ * pages; TYPE_2__* bdev; } ;
struct ttm_mem_reg {int placement; } ;
struct ttm_buffer_object {struct ttm_tt* ttm; struct ttm_mem_reg mem; } ;
struct ttm_bo_kmap_obj {unsigned long num_pages; int /*<<< orphan*/ * virtual; int /*<<< orphan*/  bo_kmap_type; int /*<<< orphan*/  sf; int /*<<< orphan*/  page; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* ttm_tt_populate ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SIZE ; 
 int TTM_PL_FLAG_CACHED ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 scalar_t__ kva_alloc (unsigned long) ; 
 int /*<<< orphan*/  pmap_page_set_memattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_qenter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sf_buf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sf_buf_kva (int /*<<< orphan*/ ) ; 
 int stub1 (struct ttm_tt*) ; 
 scalar_t__ tt_unpopulated ; 
 int /*<<< orphan*/  ttm_bo_map_kmap ; 
 int /*<<< orphan*/  ttm_bo_map_vmap ; 
 int /*<<< orphan*/  ttm_io_prot (int) ; 

__attribute__((used)) static int ttm_bo_kmap_ttm(struct ttm_buffer_object *bo,
			   unsigned long start_page,
			   unsigned long num_pages,
			   struct ttm_bo_kmap_obj *map)
{
	struct ttm_mem_reg *mem = &bo->mem;
	vm_memattr_t prot;
	struct ttm_tt *ttm = bo->ttm;
	int i, ret;

	MPASS(ttm != NULL);

	if (ttm->state == tt_unpopulated) {
		ret = ttm->bdev->driver->ttm_tt_populate(ttm);
		if (ret)
			return ret;
	}

	if (num_pages == 1 && (mem->placement & TTM_PL_FLAG_CACHED)) {
		/*
		 * We're mapping a single page, and the desired
		 * page protection is consistent with the bo.
		 */

		map->bo_kmap_type = ttm_bo_map_kmap;
		map->page = ttm->pages[start_page];
		map->sf = sf_buf_alloc(map->page, 0);
		map->virtual = (void *)sf_buf_kva(map->sf);
	} else {
		/*
		 * We need to use vmap to get the desired page protection
		 * or to make the buffer object look contiguous.
		 */
		prot = (mem->placement & TTM_PL_FLAG_CACHED) ?
			VM_MEMATTR_DEFAULT : ttm_io_prot(mem->placement);
		map->bo_kmap_type = ttm_bo_map_vmap;
		map->num_pages = num_pages;
		map->virtual = (void *)kva_alloc(num_pages * PAGE_SIZE);
		if (map->virtual != NULL) {
			for (i = 0; i < num_pages; i++) {
				/* XXXKIB hack */
				pmap_page_set_memattr(ttm->pages[start_page +
				    i], prot);
			}
			pmap_qenter((vm_offset_t)map->virtual,
			    &ttm->pages[start_page], num_pages);
		}
	}
	return (!map->virtual) ? -ENOMEM : 0;
}