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
struct ttm_mem_type_manager {int dummy; } ;
struct TYPE_4__ {size_t mem_type; } ;
struct ttm_buffer_object {TYPE_2__ mem; TYPE_1__* bdev; } ;
struct ttm_bo_kmap_obj {int bo_kmap_type; int num_pages; int /*<<< orphan*/ * sf; int /*<<< orphan*/ * page; int /*<<< orphan*/ * virtual; struct ttm_buffer_object* bo; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  kva_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_qremove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sf_buf_free (int /*<<< orphan*/ *) ; 
#define  ttm_bo_map_iomap 131 
#define  ttm_bo_map_kmap 130 
#define  ttm_bo_map_premapped 129 
#define  ttm_bo_map_vmap 128 
 int /*<<< orphan*/  ttm_mem_io_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ttm_mem_io_lock (struct ttm_mem_type_manager*,int) ; 
 int /*<<< orphan*/  ttm_mem_io_unlock (struct ttm_mem_type_manager*) ; 

void ttm_bo_kunmap(struct ttm_bo_kmap_obj *map)
{
	struct ttm_buffer_object *bo = map->bo;
	struct ttm_mem_type_manager *man =
		&bo->bdev->man[bo->mem.mem_type];

	if (!map->virtual)
		return;
	switch (map->bo_kmap_type) {
	case ttm_bo_map_iomap:
		pmap_unmapdev((vm_offset_t)map->virtual, map->size);
		break;
	case ttm_bo_map_vmap:
		pmap_qremove((vm_offset_t)(map->virtual), map->num_pages);
		kva_free((vm_offset_t)map->virtual,
		    map->num_pages * PAGE_SIZE);
		break;
	case ttm_bo_map_kmap:
		sf_buf_free(map->sf);
		break;
	case ttm_bo_map_premapped:
		break;
	default:
		MPASS(0);
	}
	(void) ttm_mem_io_lock(man, false);
	ttm_mem_io_free(map->bo->bdev, &map->bo->mem);
	ttm_mem_io_unlock(man);
	map->virtual = NULL;
	map->page = NULL;
	map->sf = NULL;
}