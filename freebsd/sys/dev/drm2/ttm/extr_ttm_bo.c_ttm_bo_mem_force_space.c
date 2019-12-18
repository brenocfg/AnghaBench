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
typedef  size_t uint32_t ;
struct ttm_placement {int dummy; } ;
struct ttm_mem_type_manager {TYPE_1__* func; } ;
struct ttm_mem_reg {size_t mem_type; int /*<<< orphan*/ * mm_node; } ;
struct ttm_buffer_object {struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;
struct TYPE_2__ {int (* get_node ) (struct ttm_mem_type_manager*,struct ttm_buffer_object*,struct ttm_placement*,struct ttm_mem_reg*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int stub1 (struct ttm_mem_type_manager*,struct ttm_buffer_object*,struct ttm_placement*,struct ttm_mem_reg*) ; 
 int ttm_mem_evict_first (struct ttm_bo_device*,size_t,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_bo_mem_force_space(struct ttm_buffer_object *bo,
					uint32_t mem_type,
					struct ttm_placement *placement,
					struct ttm_mem_reg *mem,
					bool interruptible,
					bool no_wait_gpu)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_mem_type_manager *man = &bdev->man[mem_type];
	int ret;

	do {
		ret = (*man->func->get_node)(man, bo, placement, mem);
		if (unlikely(ret != 0))
			return ret;
		if (mem->mm_node)
			break;
		ret = ttm_mem_evict_first(bdev, mem_type,
					  interruptible, no_wait_gpu);
		if (unlikely(ret != 0))
			return ret;
	} while (1);
	if (mem->mm_node == NULL)
		return -ENOMEM;
	mem->mem_type = mem_type;
	return 0;
}