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
struct ttm_placement {scalar_t__ num_busy_placement; scalar_t__ num_placement; scalar_t__ lpfn; scalar_t__ fpfn; } ;
struct TYPE_3__ {int io_reserved_vm; scalar_t__ io_reserved_count; } ;
struct ttm_mem_reg {TYPE_1__ bus; int /*<<< orphan*/ * mm_node; } ;
struct ttm_buffer_object {int evicted; struct ttm_mem_reg mem; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {TYPE_2__* driver; int /*<<< orphan*/  fence_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* evict_flags ) (struct ttm_buffer_object*,struct ttm_placement*) ;} ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct ttm_buffer_object*,struct ttm_placement*) ; 
 int ttm_bo_handle_move_mem (struct ttm_buffer_object*,struct ttm_mem_reg*,int,int,int) ; 
 int /*<<< orphan*/  ttm_bo_is_reserved (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_mem_put (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 
 int ttm_bo_mem_space (struct ttm_buffer_object*,struct ttm_placement*,struct ttm_mem_reg*,int,int) ; 
 int /*<<< orphan*/  ttm_bo_mem_space_debug (struct ttm_buffer_object*,struct ttm_placement*) ; 
 int ttm_bo_wait (struct ttm_buffer_object*,int,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_bo_evict(struct ttm_buffer_object *bo, bool interruptible,
			bool no_wait_gpu)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_mem_reg evict_mem;
	struct ttm_placement placement;
	int ret = 0;

	mtx_lock(&bdev->fence_lock);
	ret = ttm_bo_wait(bo, false, interruptible, no_wait_gpu);
	mtx_unlock(&bdev->fence_lock);

	if (unlikely(ret != 0)) {
		if (ret != -ERESTARTSYS) {
			printf("[TTM] Failed to expire sync object before buffer eviction\n");
		}
		goto out;
	}

	MPASS(ttm_bo_is_reserved(bo));

	evict_mem = bo->mem;
	evict_mem.mm_node = NULL;
	evict_mem.bus.io_reserved_vm = false;
	evict_mem.bus.io_reserved_count = 0;

	placement.fpfn = 0;
	placement.lpfn = 0;
	placement.num_placement = 0;
	placement.num_busy_placement = 0;
	bdev->driver->evict_flags(bo, &placement);
	ret = ttm_bo_mem_space(bo, &placement, &evict_mem, interruptible,
				no_wait_gpu);
	if (ret) {
		if (ret != -ERESTARTSYS) {
			printf("[TTM] Failed to find memory space for buffer 0x%p eviction\n",
			       bo);
			ttm_bo_mem_space_debug(bo, &placement);
		}
		goto out;
	}

	ret = ttm_bo_handle_move_mem(bo, &evict_mem, true, interruptible,
				     no_wait_gpu);
	if (ret) {
		if (ret != -ERESTARTSYS)
			printf("[TTM] Buffer eviction failed\n");
		ttm_bo_mem_put(bo, &evict_mem);
		goto out;
	}
	bo->evicted = true;
out:
	return ret;
}