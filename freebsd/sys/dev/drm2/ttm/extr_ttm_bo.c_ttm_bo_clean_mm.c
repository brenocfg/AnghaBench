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
struct ttm_mem_type_manager {int has_type; int use_type; TYPE_1__* func; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;
struct TYPE_2__ {int (* takedown ) (struct ttm_mem_type_manager*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TTM_NUM_MEM_TYPES ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int stub1 (struct ttm_mem_type_manager*) ; 
 int /*<<< orphan*/  ttm_bo_force_list_clean (struct ttm_bo_device*,unsigned int,int) ; 

int ttm_bo_clean_mm(struct ttm_bo_device *bdev, unsigned mem_type)
{
	struct ttm_mem_type_manager *man;
	int ret = -EINVAL;

	if (mem_type >= TTM_NUM_MEM_TYPES) {
		printf("[TTM] Illegal memory type %d\n", mem_type);
		return ret;
	}
	man = &bdev->man[mem_type];

	if (!man->has_type) {
		printf("[TTM] Trying to take down uninitialized memory manager type %u\n",
		       mem_type);
		return ret;
	}

	man->use_type = false;
	man->has_type = false;

	ret = 0;
	if (mem_type > 0) {
		ttm_bo_force_list_clean(bdev, mem_type, false);

		ret = (*man->func->takedown)(man);
	}

	return ret;
}