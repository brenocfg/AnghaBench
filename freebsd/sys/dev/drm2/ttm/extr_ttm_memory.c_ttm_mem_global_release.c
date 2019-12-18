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
struct ttm_mem_zone {int /*<<< orphan*/  kobj_ref; } ;
struct ttm_mem_global {unsigned int num_zones; int /*<<< orphan*/  kobj_ref; struct ttm_mem_zone** zones; int /*<<< orphan*/ * swap_queue; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_dma_page_alloc_fini () ; 
 int /*<<< orphan*/  ttm_mem_global_kobj_release (struct ttm_mem_global*) ; 
 int /*<<< orphan*/  ttm_mem_zone_kobj_release (struct ttm_mem_zone*) ; 
 int /*<<< orphan*/  ttm_page_alloc_fini () ; 

void ttm_mem_global_release(struct ttm_mem_global *glob)
{
	unsigned int i;
	struct ttm_mem_zone *zone;

	/* let the page allocator first stop the shrink work. */
	ttm_page_alloc_fini();
	ttm_dma_page_alloc_fini();

	taskqueue_drain(glob->swap_queue, &glob->work);
	taskqueue_free(glob->swap_queue);
	glob->swap_queue = NULL;
	for (i = 0; i < glob->num_zones; ++i) {
		zone = glob->zones[i];
		if (refcount_release(&zone->kobj_ref))
			ttm_mem_zone_kobj_release(zone);
	}
	if (refcount_release(&glob->kobj_ref))
		ttm_mem_global_kobj_release(glob);
}