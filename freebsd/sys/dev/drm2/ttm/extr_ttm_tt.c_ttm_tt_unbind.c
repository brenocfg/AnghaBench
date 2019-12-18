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
struct ttm_tt {scalar_t__ state; TYPE_1__* func; } ;
struct TYPE_2__ {int (* unbind ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int stub1 (struct ttm_tt*) ; 
 scalar_t__ tt_bound ; 
 scalar_t__ tt_unbound ; 

void ttm_tt_unbind(struct ttm_tt *ttm)
{
	int ret;

	if (ttm->state == tt_bound) {
		ret = ttm->func->unbind(ttm);
		MPASS(ret == 0);
		ttm->state = tt_unbound;
	}
}