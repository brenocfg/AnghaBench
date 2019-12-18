#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_type_manager {int has_type; int io_reserve_fastpath; int use_io_reserve_lru; int use_type; unsigned long size; int /*<<< orphan*/  lru; TYPE_2__* func; struct ttm_bo_device* bdev; int /*<<< orphan*/  io_reserve_lru; int /*<<< orphan*/  io_reserve_mutex; } ;
struct ttm_bo_device {TYPE_1__* driver; struct ttm_mem_type_manager* man; } ;
struct TYPE_4__ {int (* init ) (struct ttm_mem_type_manager*,unsigned long) ;} ;
struct TYPE_3__ {int (* init_mem_type ) (struct ttm_bo_device*,unsigned int,struct ttm_mem_type_manager*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 unsigned int TTM_NUM_MEM_TYPES ; 
 unsigned int TTM_PL_SYSTEM ; 
 int stub1 (struct ttm_bo_device*,unsigned int,struct ttm_mem_type_manager*) ; 
 int stub2 (struct ttm_mem_type_manager*,unsigned long) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

int ttm_bo_init_mm(struct ttm_bo_device *bdev, unsigned type,
			unsigned long p_size)
{
	int ret = -EINVAL;
	struct ttm_mem_type_manager *man;

	MPASS(type < TTM_NUM_MEM_TYPES);
	man = &bdev->man[type];
	MPASS(!man->has_type);
	man->io_reserve_fastpath = true;
	man->use_io_reserve_lru = false;
	sx_init(&man->io_reserve_mutex, "ttmman");
	INIT_LIST_HEAD(&man->io_reserve_lru);

	ret = bdev->driver->init_mem_type(bdev, type, man);
	if (ret)
		return ret;
	man->bdev = bdev;

	ret = 0;
	if (type != TTM_PL_SYSTEM) {
		ret = (*man->func->init)(man, p_size);
		if (ret)
			return ret;
	}
	man->has_type = true;
	man->use_type = true;
	man->size = p_size;

	INIT_LIST_HEAD(&man->lru);

	return 0;
}