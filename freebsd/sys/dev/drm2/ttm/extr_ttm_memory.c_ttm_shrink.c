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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_mem_shrink {int (* do_shrink ) (struct ttm_mem_shrink*) ;} ;
struct ttm_mem_global {int /*<<< orphan*/  lock; struct ttm_mem_shrink* shrink; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ttm_mem_shrink*) ; 
 scalar_t__ ttm_zones_above_swap_target (struct ttm_mem_global*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ttm_shrink(struct ttm_mem_global *glob, bool from_wq,
		       uint64_t extra)
{
	int ret;
	struct ttm_mem_shrink *shrink;

	mtx_lock(&glob->lock);
	if (glob->shrink == NULL)
		goto out;

	while (ttm_zones_above_swap_target(glob, from_wq, extra)) {
		shrink = glob->shrink;
		mtx_unlock(&glob->lock);
		ret = shrink->do_shrink(shrink);
		mtx_lock(&glob->lock);
		if (unlikely(ret != 0))
			goto out;
	}
out:
	mtx_unlock(&glob->lock);
}