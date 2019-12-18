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
typedef  int u_int64_t ;
struct ttm_mem_zone {char* name; scalar_t__ max_mem; } ;
struct ttm_mem_global {int num_zones; TYPE_1__* zone_kernel; struct ttm_mem_zone** zones; int /*<<< orphan*/  kobj_ref; int /*<<< orphan*/  work; int /*<<< orphan*/  swap_queue; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int max_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PVM ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_mem_global*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int physmem ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long long) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  ttm_dma_page_alloc_init (struct ttm_mem_global*,int) ; 
 int /*<<< orphan*/  ttm_mem_global_release (struct ttm_mem_global*) ; 
 int ttm_mem_init_dma32_zone (struct ttm_mem_global*,int) ; 
 int ttm_mem_init_kernel_zone (struct ttm_mem_global*,int) ; 
 int /*<<< orphan*/  ttm_page_alloc_init (struct ttm_mem_global*,int) ; 
 int /*<<< orphan*/  ttm_shrink_work ; 
 scalar_t__ unlikely (int) ; 

int ttm_mem_global_init(struct ttm_mem_global *glob)
{
	u_int64_t mem;
	int ret;
	int i;
	struct ttm_mem_zone *zone;

	mtx_init(&glob->lock, "ttmgz", NULL, MTX_DEF);
	glob->swap_queue = taskqueue_create("ttm_swap", M_WAITOK,
	    taskqueue_thread_enqueue, &glob->swap_queue);
	taskqueue_start_threads(&glob->swap_queue, 1, PVM, "ttm swap");
	TASK_INIT(&glob->work, 0, ttm_shrink_work, glob);

	refcount_init(&glob->kobj_ref, 1);

	mem = physmem * PAGE_SIZE;

	ret = ttm_mem_init_kernel_zone(glob, mem);
	if (unlikely(ret != 0))
		goto out_no_zone;
	ret = ttm_mem_init_dma32_zone(glob, mem);
	if (unlikely(ret != 0))
		goto out_no_zone;
	for (i = 0; i < glob->num_zones; ++i) {
		zone = glob->zones[i];
		printf("[TTM] Zone %7s: Available graphics memory: %llu kiB\n",
			zone->name, (unsigned long long)zone->max_mem >> 10);
	}
	ttm_page_alloc_init(glob, glob->zone_kernel->max_mem/(2*PAGE_SIZE));
	ttm_dma_page_alloc_init(glob, glob->zone_kernel->max_mem/(2*PAGE_SIZE));
	return 0;
out_no_zone:
	ttm_mem_global_release(glob);
	return ret;
}