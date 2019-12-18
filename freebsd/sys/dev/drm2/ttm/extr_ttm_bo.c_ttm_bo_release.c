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
struct ttm_mem_type_manager {int dummy; } ;
struct TYPE_2__ {size_t mem_type; } ;
struct ttm_buffer_object {int /*<<< orphan*/  list_kref; int /*<<< orphan*/ * vm_node; TYPE_1__ mem; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {int /*<<< orphan*/  vm_lock; int /*<<< orphan*/  addr_space_rb; struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  drm_mm_put_block (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_cleanup_refs_or_queue (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_device_buffer_objects ; 
 int /*<<< orphan*/  ttm_bo_release_list (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_mem_io_free_vm (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_mem_io_lock (struct ttm_mem_type_manager*,int) ; 
 int /*<<< orphan*/  ttm_mem_io_unlock (struct ttm_mem_type_manager*) ; 

__attribute__((used)) static void ttm_bo_release(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_mem_type_manager *man = &bdev->man[bo->mem.mem_type];

	rw_wlock(&bdev->vm_lock);
	if (likely(bo->vm_node != NULL)) {
		RB_REMOVE(ttm_bo_device_buffer_objects,
		    &bdev->addr_space_rb, bo);
		drm_mm_put_block(bo->vm_node);
		bo->vm_node = NULL;
	}
	rw_wunlock(&bdev->vm_lock);
	ttm_mem_io_lock(man, false);
	ttm_mem_io_free_vm(bo);
	ttm_mem_io_unlock(man);
	ttm_bo_cleanup_refs_or_queue(bo);
	if (refcount_release(&bo->list_kref))
		ttm_bo_release_list(bo);
}