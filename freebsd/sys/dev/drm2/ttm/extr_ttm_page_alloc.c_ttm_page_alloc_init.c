#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_global {int dummy; } ;
struct TYPE_5__ {unsigned int max_size; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  small; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj_ref; TYPE_1__ options; int /*<<< orphan*/  uc_pool_dma32; int /*<<< orphan*/  wc_pool_dma32; int /*<<< orphan*/  uc_pool; int /*<<< orphan*/  wc_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_POOLMGR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NUM_PAGES_TO_ALLOC ; 
 int /*<<< orphan*/  SMALL_ALLOCATION ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_DMA32 ; 
 TYPE_2__* _manager ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_page_pool_init_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ttm_pool_mm_shrink_init (TYPE_2__*) ; 

int ttm_page_alloc_init(struct ttm_mem_global *glob, unsigned max_pages)
{

	if (_manager != NULL)
		printf("[TTM] manager != NULL\n");
	printf("[TTM] Initializing pool allocator\n");

	_manager = malloc(sizeof(*_manager), M_TTM_POOLMGR, M_WAITOK | M_ZERO);

	ttm_page_pool_init_locked(&_manager->wc_pool, 0, "wc");
	ttm_page_pool_init_locked(&_manager->uc_pool, 0, "uc");
	ttm_page_pool_init_locked(&_manager->wc_pool_dma32,
	    TTM_PAGE_FLAG_DMA32, "wc dma");
	ttm_page_pool_init_locked(&_manager->uc_pool_dma32,
	    TTM_PAGE_FLAG_DMA32, "uc dma");

	_manager->options.max_size = max_pages;
	_manager->options.small = SMALL_ALLOCATION;
	_manager->options.alloc_size = NUM_PAGES_TO_ALLOC;

	refcount_init(&_manager->kobj_ref, 1);
	ttm_pool_mm_shrink_init(_manager);

	return 0;
}