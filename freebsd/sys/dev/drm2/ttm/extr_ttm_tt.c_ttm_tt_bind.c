#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_tt {scalar_t__ state; TYPE_3__* func; TYPE_2__* bdev; } ;
struct ttm_mem_reg {int dummy; } ;
struct TYPE_6__ {int (* bind ) (struct ttm_tt*,struct ttm_mem_reg*) ;} ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int (* ttm_tt_populate ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct ttm_tt*) ; 
 int stub2 (struct ttm_tt*,struct ttm_mem_reg*) ; 
 scalar_t__ tt_bound ; 
 scalar_t__ unlikely (int) ; 

int ttm_tt_bind(struct ttm_tt *ttm, struct ttm_mem_reg *bo_mem)
{
	int ret = 0;

	if (!ttm)
		return -EINVAL;

	if (ttm->state == tt_bound)
		return 0;

	ret = ttm->bdev->driver->ttm_tt_populate(ttm);
	if (ret)
		return ret;

	ret = ttm->func->bind(ttm, bo_mem);
	if (unlikely(ret != 0))
		return ret;

	ttm->state = tt_bound;

	return 0;
}