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
struct ttm_mem_type_manager {int /*<<< orphan*/  io_reserve_fastpath; } ;
struct TYPE_3__ {int /*<<< orphan*/  io_reserved_count; } ;
struct ttm_mem_reg {size_t mem_type; TYPE_1__ bus; } ;
struct ttm_bo_device {TYPE_2__* driver; struct ttm_mem_type_manager* man; } ;
struct TYPE_4__ {int (* io_mem_reserve ) (struct ttm_bo_device*,struct ttm_mem_reg*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int stub1 (struct ttm_bo_device*,struct ttm_mem_reg*) ; 
 int stub2 (struct ttm_bo_device*,struct ttm_mem_reg*) ; 
 int ttm_mem_io_evict (struct ttm_mem_type_manager*) ; 

__attribute__((used)) static int ttm_mem_io_reserve(struct ttm_bo_device *bdev,
			      struct ttm_mem_reg *mem)
{
	struct ttm_mem_type_manager *man = &bdev->man[mem->mem_type];
	int ret = 0;

	if (!bdev->driver->io_mem_reserve)
		return 0;
	if (likely(man->io_reserve_fastpath))
		return bdev->driver->io_mem_reserve(bdev, mem);

	if (bdev->driver->io_mem_reserve &&
	    mem->bus.io_reserved_count++ == 0) {
retry:
		ret = bdev->driver->io_mem_reserve(bdev, mem);
		if (ret == -EAGAIN) {
			ret = ttm_mem_io_evict(man);
			if (ret == 0)
				goto retry;
		}
	}
	return ret;
}