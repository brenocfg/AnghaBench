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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ISA_POOL_SIZE ; 
 int /*<<< orphan*/  init_bounce_bioset () ; 
 int /*<<< orphan*/  isa_mutex ; 
 int /*<<< orphan*/  isa_page_pool ; 
 int /*<<< orphan*/  mempool_alloc_pages_isa ; 
 int /*<<< orphan*/  mempool_free_pages ; 
 int mempool_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ mempool_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int init_emergency_isa_pool(void)
{
	int ret;

	mutex_lock(&isa_mutex);

	if (mempool_initialized(&isa_page_pool)) {
		mutex_unlock(&isa_mutex);
		return 0;
	}

	ret = mempool_init(&isa_page_pool, ISA_POOL_SIZE, mempool_alloc_pages_isa,
			   mempool_free_pages, (void *) 0);
	BUG_ON(ret);

	pr_info("isa pool size: %d pages\n", ISA_POOL_SIZE);
	init_bounce_bioset();
	mutex_unlock(&isa_mutex);
	return 0;
}