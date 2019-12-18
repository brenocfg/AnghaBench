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
struct ttm_mem_type_manager {int flags; } ;
struct ttm_mem_reg {size_t mem_type; int /*<<< orphan*/ * mm_node; } ;
struct ttm_buffer_object {int /*<<< orphan*/ * ttm; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * sync_obj; struct ttm_mem_reg mem; struct ttm_bo_device* bdev; } ;
struct ttm_bo_driver {int /*<<< orphan*/  (* sync_obj_unref ) (void**) ;int /*<<< orphan*/ * (* sync_obj_ref ) (void*) ;} ;
struct ttm_bo_device {int /*<<< orphan*/  fence_lock; struct ttm_mem_type_manager* man; struct ttm_bo_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_BO_PRIV_FLAG_MOVING ; 
 int TTM_MEMTYPE_FLAG_FIXED ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void**) ; 
 int /*<<< orphan*/  stub3 (void**) ; 
 int /*<<< orphan*/  ttm_bo_free_old_node (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_unref (struct ttm_buffer_object**) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_wait (struct ttm_buffer_object*,int,int,int) ; 
 int ttm_buffer_object_transfer (struct ttm_buffer_object*,struct ttm_buffer_object**) ; 
 int /*<<< orphan*/  ttm_tt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_tt_unbind (int /*<<< orphan*/ *) ; 

int ttm_bo_move_accel_cleanup(struct ttm_buffer_object *bo,
			      void *sync_obj,
			      bool evict,
			      bool no_wait_gpu,
			      struct ttm_mem_reg *new_mem)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_bo_driver *driver = bdev->driver;
	struct ttm_mem_type_manager *man = &bdev->man[new_mem->mem_type];
	struct ttm_mem_reg *old_mem = &bo->mem;
	int ret;
	struct ttm_buffer_object *ghost_obj;
	void *tmp_obj = NULL;

	mtx_lock(&bdev->fence_lock);
	if (bo->sync_obj) {
		tmp_obj = bo->sync_obj;
		bo->sync_obj = NULL;
	}
	bo->sync_obj = driver->sync_obj_ref(sync_obj);
	if (evict) {
		ret = ttm_bo_wait(bo, false, false, false);
		mtx_unlock(&bdev->fence_lock);
		if (tmp_obj)
			driver->sync_obj_unref(&tmp_obj);
		if (ret)
			return ret;

		if ((man->flags & TTM_MEMTYPE_FLAG_FIXED) &&
		    (bo->ttm != NULL)) {
			ttm_tt_unbind(bo->ttm);
			ttm_tt_destroy(bo->ttm);
			bo->ttm = NULL;
		}
		ttm_bo_free_old_node(bo);
	} else {
		/**
		 * This should help pipeline ordinary buffer moves.
		 *
		 * Hang old buffer memory on a new buffer object,
		 * and leave it to be released when the GPU
		 * operation has completed.
		 */

		set_bit(TTM_BO_PRIV_FLAG_MOVING, &bo->priv_flags);
		mtx_unlock(&bdev->fence_lock);
		if (tmp_obj)
			driver->sync_obj_unref(&tmp_obj);

		ret = ttm_buffer_object_transfer(bo, &ghost_obj);
		if (ret)
			return ret;

		/**
		 * If we're not moving to fixed memory, the TTM object
		 * needs to stay alive. Otherwhise hang it on the ghost
		 * bo to be unbound and destroyed.
		 */

		if (!(man->flags & TTM_MEMTYPE_FLAG_FIXED))
			ghost_obj->ttm = NULL;
		else
			bo->ttm = NULL;

		ttm_bo_unreserve(ghost_obj);
		ttm_bo_unref(&ghost_obj);
	}

	*old_mem = *new_mem;
	new_mem->mm_node = NULL;

	return 0;
}