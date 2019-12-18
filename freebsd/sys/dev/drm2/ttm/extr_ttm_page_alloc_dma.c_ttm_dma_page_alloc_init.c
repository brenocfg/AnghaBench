#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_global {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {unsigned int max_size; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  small; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; TYPE_1__ options; int /*<<< orphan*/  pools; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUM_PAGES_TO_ALLOC ; 
 int /*<<< orphan*/  SMALL_ALLOCATION ; 
 int /*<<< orphan*/  WARN_ON (TYPE_2__*) ; 
 TYPE_2__* _manager ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  ttm_dma_pool_mm_shrink_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ttm_pool_kobj_type ; 
 scalar_t__ unlikely (int) ; 

int ttm_dma_page_alloc_init(struct ttm_mem_global *glob, unsigned max_pages)
{
	int ret = -ENOMEM;

	WARN_ON(_manager);

	pr_info("Initializing DMA pool allocator\n");

	_manager = kzalloc(sizeof(*_manager), GFP_KERNEL);
	if (!_manager)
		goto err;

	mutex_init(&_manager->lock);
	INIT_LIST_HEAD(&_manager->pools);

	_manager->options.max_size = max_pages;
	_manager->options.small = SMALL_ALLOCATION;
	_manager->options.alloc_size = NUM_PAGES_TO_ALLOC;

	/* This takes care of auto-freeing the _manager */
	ret = kobject_init_and_add(&_manager->kobj, &ttm_pool_kobj_type,
				   &glob->kobj, "dma_pool");
	if (unlikely(ret != 0)) {
		kobject_put(&_manager->kobj);
		goto err;
	}
	ttm_dma_pool_mm_shrink_init(_manager);
	return 0;
err:
	return ret;
}