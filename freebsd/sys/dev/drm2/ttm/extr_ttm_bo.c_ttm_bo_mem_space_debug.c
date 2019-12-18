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
struct ttm_placement {int num_placement; int* placement; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  num_pages; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ttm_mem_type_debug (int /*<<< orphan*/ ,int) ; 
 int ttm_mem_type_from_flags (int,int*) ; 

__attribute__((used)) static void ttm_bo_mem_space_debug(struct ttm_buffer_object *bo,
					struct ttm_placement *placement)
{
	int i, ret, mem_type;

	printf("No space for %p (%lu pages, %luK, %luM)\n",
	       bo, bo->mem.num_pages, bo->mem.size >> 10,
	       bo->mem.size >> 20);
	for (i = 0; i < placement->num_placement; i++) {
		ret = ttm_mem_type_from_flags(placement->placement[i],
						&mem_type);
		if (ret)
			return;
		printf("  placement[%d]=0x%08X (%d)\n",
		       i, placement->placement[i], mem_type);
		ttm_mem_type_debug(bo->bdev, mem_type);
	}
}