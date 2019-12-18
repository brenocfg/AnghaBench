#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_type_manager {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_iomem; } ;
struct TYPE_6__ {size_t mem_type; TYPE_1__ bus; } ;
struct ttm_buffer_object {unsigned long num_pages; TYPE_3__ mem; TYPE_2__* bdev; int /*<<< orphan*/  swap; } ;
struct ttm_bo_kmap_obj {struct ttm_buffer_object* bo; int /*<<< orphan*/ * virtual; } ;
struct TYPE_5__ {struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CURPROC ; 
 int /*<<< orphan*/  DRM_SUSER (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int ttm_bo_ioremap (struct ttm_buffer_object*,unsigned long,unsigned long,struct ttm_bo_kmap_obj*) ; 
 int ttm_bo_kmap_ttm (struct ttm_buffer_object*,unsigned long,unsigned long,struct ttm_bo_kmap_obj*) ; 
 int /*<<< orphan*/  ttm_mem_io_lock (struct ttm_mem_type_manager*,int) ; 
 int ttm_mem_io_reserve (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ttm_mem_io_unlock (struct ttm_mem_type_manager*) ; 

int ttm_bo_kmap(struct ttm_buffer_object *bo,
		unsigned long start_page, unsigned long num_pages,
		struct ttm_bo_kmap_obj *map)
{
	struct ttm_mem_type_manager *man =
		&bo->bdev->man[bo->mem.mem_type];
	unsigned long offset, size;
	int ret;

	MPASS(list_empty(&bo->swap));
	map->virtual = NULL;
	map->bo = bo;
	if (num_pages > bo->num_pages)
		return -EINVAL;
	if (start_page > bo->num_pages)
		return -EINVAL;
#if 0
	if (num_pages > 1 && !DRM_SUSER(DRM_CURPROC))
		return -EPERM;
#endif
	(void) ttm_mem_io_lock(man, false);
	ret = ttm_mem_io_reserve(bo->bdev, &bo->mem);
	ttm_mem_io_unlock(man);
	if (ret)
		return ret;
	if (!bo->mem.bus.is_iomem) {
		return ttm_bo_kmap_ttm(bo, start_page, num_pages, map);
	} else {
		offset = start_page << PAGE_SHIFT;
		size = num_pages << PAGE_SHIFT;
		return ttm_bo_ioremap(bo, offset, size, map);
	}
}