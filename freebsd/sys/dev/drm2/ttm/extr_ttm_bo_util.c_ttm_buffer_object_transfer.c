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
struct ttm_buffer_object {scalar_t__ acc_size; int /*<<< orphan*/ * destroy; int /*<<< orphan*/  kref; int /*<<< orphan*/  list_kref; int /*<<< orphan*/ * sync_obj; int /*<<< orphan*/  cpu_writers; int /*<<< orphan*/ * vm_node; int /*<<< orphan*/  io_reserve_lru; int /*<<< orphan*/  swap; int /*<<< orphan*/  lru; int /*<<< orphan*/  ddestroy; struct ttm_bo_device* bdev; } ;
struct ttm_bo_driver {int /*<<< orphan*/ * (* sync_obj_ref ) (int /*<<< orphan*/ *) ;} ;
struct ttm_bo_device {int /*<<< orphan*/  fence_lock; struct ttm_bo_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_TTM_TRANSF_OBJ ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ttm_buffer_object* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_transfered_destroy ; 

__attribute__((used)) static int
ttm_buffer_object_transfer(struct ttm_buffer_object *bo,
    struct ttm_buffer_object **new_obj)
{
	struct ttm_buffer_object *fbo;
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_bo_driver *driver = bdev->driver;

	fbo = malloc(sizeof(*fbo), M_TTM_TRANSF_OBJ, M_WAITOK);
	*fbo = *bo;

	/**
	 * Fix up members that we shouldn't copy directly:
	 * TODO: Explicit member copy would probably be better here.
	 */

	INIT_LIST_HEAD(&fbo->ddestroy);
	INIT_LIST_HEAD(&fbo->lru);
	INIT_LIST_HEAD(&fbo->swap);
	INIT_LIST_HEAD(&fbo->io_reserve_lru);
	fbo->vm_node = NULL;
	atomic_set(&fbo->cpu_writers, 0);

	mtx_lock(&bdev->fence_lock);
	if (bo->sync_obj)
		fbo->sync_obj = driver->sync_obj_ref(bo->sync_obj);
	else
		fbo->sync_obj = NULL;
	mtx_unlock(&bdev->fence_lock);
	refcount_init(&fbo->list_kref, 1);
	refcount_init(&fbo->kref, 1);
	fbo->destroy = &ttm_transfered_destroy;
	fbo->acc_size = 0;

	*new_obj = fbo;
	return 0;
}