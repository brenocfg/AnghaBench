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
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_pool_manager*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_pool_mm_shrink ; 
 int /*<<< orphan*/  vm_lowmem ; 

__attribute__((used)) static void ttm_pool_mm_shrink_init(struct ttm_pool_manager *manager)
{

	manager->lowmem_handler = EVENTHANDLER_REGISTER(vm_lowmem,
	    ttm_pool_mm_shrink, manager, EVENTHANDLER_PRI_ANY);
}