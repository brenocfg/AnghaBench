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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ base; scalar_t__ addr; } ;
struct ttm_mem_reg {int placement; TYPE_1__ bus; } ;
struct ttm_buffer_object {struct ttm_mem_reg mem; } ;
struct ttm_bo_kmap_obj {unsigned long size; void* virtual; int /*<<< orphan*/  bo_kmap_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TTM_PL_FLAG_WC ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 void* pmap_mapdev_attr (scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_map_iomap ; 
 int /*<<< orphan*/  ttm_bo_map_premapped ; 

__attribute__((used)) static int ttm_bo_ioremap(struct ttm_buffer_object *bo,
			  unsigned long offset,
			  unsigned long size,
			  struct ttm_bo_kmap_obj *map)
{
	struct ttm_mem_reg *mem = &bo->mem;

	if (bo->mem.bus.addr) {
		map->bo_kmap_type = ttm_bo_map_premapped;
		map->virtual = (void *)(((u8 *)bo->mem.bus.addr) + offset);
	} else {
		map->bo_kmap_type = ttm_bo_map_iomap;
		map->virtual = pmap_mapdev_attr(bo->mem.bus.base +
		    bo->mem.bus.offset + offset, size,
		    (mem->placement & TTM_PL_FLAG_WC) ?
		    VM_MEMATTR_WRITE_COMBINING : VM_MEMATTR_UNCACHEABLE);
		map->size = size;
	}
	return (!map->virtual) ? -ENOMEM : 0;
}