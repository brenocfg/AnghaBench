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
struct ttm_pool_manager {int /*<<< orphan*/  lowmem_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_lowmem ; 

__attribute__((used)) static void ttm_pool_mm_shrink_fini(struct ttm_pool_manager *manager)
{

	EVENTHANDLER_DEREGISTER(vm_lowmem, manager->lowmem_handler);
}