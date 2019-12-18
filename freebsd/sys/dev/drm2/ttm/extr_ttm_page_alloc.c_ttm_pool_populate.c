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
struct ttm_tt {scalar_t__ state; unsigned int num_pages; int page_flags; int /*<<< orphan*/ * pages; int /*<<< orphan*/  caching_state; TYPE_1__* glob; } ;
struct ttm_mem_global {int dummy; } ;
struct TYPE_2__ {struct ttm_mem_global* mem_glob; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TTM_PAGE_FLAG_SWAPPED ; 
 scalar_t__ tt_unbound ; 
 scalar_t__ tt_unpopulated ; 
 int ttm_get_pages (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int ttm_mem_global_alloc_page (struct ttm_mem_global*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (struct ttm_tt*) ; 
 int ttm_tt_swapin (struct ttm_tt*) ; 
 scalar_t__ unlikely (int) ; 

int ttm_pool_populate(struct ttm_tt *ttm)
{
	struct ttm_mem_global *mem_glob = ttm->glob->mem_glob;
	unsigned i;
	int ret;

	if (ttm->state != tt_unpopulated)
		return 0;

	for (i = 0; i < ttm->num_pages; ++i) {
		ret = ttm_get_pages(&ttm->pages[i], 1,
				    ttm->page_flags,
				    ttm->caching_state);
		if (ret != 0) {
			ttm_pool_unpopulate(ttm);
			return -ENOMEM;
		}

		ret = ttm_mem_global_alloc_page(mem_glob, ttm->pages[i],
						false, false);
		if (unlikely(ret != 0)) {
			ttm_pool_unpopulate(ttm);
			return -ENOMEM;
		}
	}

	if (unlikely(ttm->page_flags & TTM_PAGE_FLAG_SWAPPED)) {
		ret = ttm_tt_swapin(ttm);
		if (unlikely(ret != 0)) {
			ttm_pool_unpopulate(ttm);
			return ret;
		}
	}

	ttm->state = tt_unbound;
	return 0;
}