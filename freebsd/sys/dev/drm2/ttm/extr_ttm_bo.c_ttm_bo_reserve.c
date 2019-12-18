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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_buffer_object {struct ttm_bo_global* glob; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_list_ref_sub (struct ttm_buffer_object*,int,int) ; 
 int ttm_bo_reserve_nolru (struct ttm_buffer_object*,int,int,int,int /*<<< orphan*/ ) ; 

int ttm_bo_reserve(struct ttm_buffer_object *bo,
		   bool interruptible,
		   bool no_wait, bool use_sequence, uint32_t sequence)
{
	struct ttm_bo_global *glob = bo->glob;
	int put_count = 0;
	int ret;

	mtx_lock(&bo->glob->lru_lock);
	ret = ttm_bo_reserve_nolru(bo, interruptible, no_wait, use_sequence,
				   sequence);
	if (likely(ret == 0)) {
		put_count = ttm_bo_del_from_lru(bo);
		mtx_unlock(&glob->lru_lock);
		ttm_bo_list_ref_sub(bo, put_count, true);
	} else
		mtx_unlock(&bo->glob->lru_lock);

	return ret;
}