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
struct ttm_buffer_object {int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  reserved; scalar_t__ sync_obj; struct ttm_bo_global* glob; struct ttm_bo_device* bdev; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct ttm_bo_driver {int /*<<< orphan*/  (* sync_obj_unref ) (void**) ;int /*<<< orphan*/  (* sync_obj_flush ) (void*) ;void* (* sync_obj_ref ) (scalar_t__) ;} ;
struct ttm_bo_device {int /*<<< orphan*/  wq; int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  fence_lock; struct ttm_bo_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 void* stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void**) ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  ttm_bo_cleanup_memtype_use (struct ttm_buffer_object*) ; 
 int ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_list_ref_sub (struct ttm_buffer_object*,int,int) ; 
 int ttm_bo_reserve_nolru (struct ttm_buffer_object*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_wait (struct ttm_buffer_object*,int,int,int) ; 
 int /*<<< orphan*/  wakeup (struct ttm_buffer_object*) ; 

__attribute__((used)) static void ttm_bo_cleanup_refs_or_queue(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_bo_global *glob = bo->glob;
	struct ttm_bo_driver *driver = bdev->driver;
	void *sync_obj = NULL;
	int put_count;
	int ret;

	mtx_lock(&glob->lru_lock);
	ret = ttm_bo_reserve_nolru(bo, false, true, false, 0);

	mtx_lock(&bdev->fence_lock);
	(void) ttm_bo_wait(bo, false, false, true);
	if (!ret && !bo->sync_obj) {
		mtx_unlock(&bdev->fence_lock);
		put_count = ttm_bo_del_from_lru(bo);

		mtx_unlock(&glob->lru_lock);
		ttm_bo_cleanup_memtype_use(bo);

		ttm_bo_list_ref_sub(bo, put_count, true);

		return;
	}
	if (bo->sync_obj)
		sync_obj = driver->sync_obj_ref(bo->sync_obj);
	mtx_unlock(&bdev->fence_lock);

	if (!ret) {
		atomic_set(&bo->reserved, 0);
		wakeup(bo);
	}

	refcount_acquire(&bo->list_kref);
	list_add_tail(&bo->ddestroy, &bdev->ddestroy);
	mtx_unlock(&glob->lru_lock);

	if (sync_obj) {
		driver->sync_obj_flush(sync_obj);
		driver->sync_obj_unref(&sync_obj);
	}
	taskqueue_enqueue_timeout(taskqueue_thread, &bdev->wq,
	    ((hz / 100) < 1) ? 1 : hz / 100);
}