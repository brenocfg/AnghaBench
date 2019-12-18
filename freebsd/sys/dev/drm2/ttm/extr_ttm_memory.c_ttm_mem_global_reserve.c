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
typedef  scalar_t__ uint64_t ;
struct ttm_mem_zone {scalar_t__ emer_mem; scalar_t__ max_mem; scalar_t__ used_mem; } ;
struct ttm_mem_global {unsigned int num_zones; int /*<<< orphan*/  lock; struct ttm_mem_zone** zones; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PRIV_VM_MLOCK ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_check_swapping (struct ttm_mem_global*) ; 

__attribute__((used)) static int ttm_mem_global_reserve(struct ttm_mem_global *glob,
				  struct ttm_mem_zone *single_zone,
				  uint64_t amount, bool reserve)
{
	uint64_t limit;
	int ret = -ENOMEM;
	unsigned int i;
	struct ttm_mem_zone *zone;

	mtx_lock(&glob->lock);
	for (i = 0; i < glob->num_zones; ++i) {
		zone = glob->zones[i];
		if (single_zone && zone != single_zone)
			continue;

		limit = (priv_check(curthread, PRIV_VM_MLOCK) == 0) ?
			zone->emer_mem : zone->max_mem;

		if (zone->used_mem > limit)
			goto out_unlock;
	}

	if (reserve) {
		for (i = 0; i < glob->num_zones; ++i) {
			zone = glob->zones[i];
			if (single_zone && zone != single_zone)
				continue;
			zone->used_mem += amount;
		}
	}

	ret = 0;
out_unlock:
	mtx_unlock(&glob->lock);
	ttm_check_swapping(glob);

	return ret;
}