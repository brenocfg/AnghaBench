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
struct ttm_buffer_object {int /*<<< orphan*/  cpu_writers; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {int /*<<< orphan*/  fence_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_wait (struct ttm_buffer_object*,int,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_synccpu_write_grab(struct ttm_buffer_object *bo, bool no_wait)
{
	struct ttm_bo_device *bdev = bo->bdev;
	int ret = 0;

	/*
	 * Using ttm_bo_reserve makes sure the lru lists are updated.
	 */

	ret = ttm_bo_reserve(bo, true, no_wait, false, 0);
	if (unlikely(ret != 0))
		return ret;
	mtx_lock(&bdev->fence_lock);
	ret = ttm_bo_wait(bo, false, true, no_wait);
	mtx_unlock(&bdev->fence_lock);
	if (likely(ret == 0))
		atomic_inc(&bo->cpu_writers);
	ttm_bo_unreserve(bo);
	return ret;
}