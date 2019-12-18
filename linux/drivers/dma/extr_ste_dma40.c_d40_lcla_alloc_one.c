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
struct d40_desc {int /*<<< orphan*/  lcla_alloc; } ;
struct d40_chan {TYPE_3__* base; TYPE_1__* phy_chan; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; struct d40_desc** alloc_map; } ;
struct TYPE_6__ {TYPE_2__ lcla_pool; } ;
struct TYPE_4__ {int num; } ;

/* Variables and functions */
 int D40_LCLA_LINK_PER_EVENT_GRP ; 
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int d40_lcla_alloc_one(struct d40_chan *d40c,
			      struct d40_desc *d40d)
{
	unsigned long flags;
	int i;
	int ret = -EINVAL;

	spin_lock_irqsave(&d40c->base->lcla_pool.lock, flags);

	/*
	 * Allocate both src and dst at the same time, therefore the half
	 * start on 1 since 0 can't be used since zero is used as end marker.
	 */
	for (i = 1 ; i < D40_LCLA_LINK_PER_EVENT_GRP / 2; i++) {
		int idx = d40c->phy_chan->num * D40_LCLA_LINK_PER_EVENT_GRP + i;

		if (!d40c->base->lcla_pool.alloc_map[idx]) {
			d40c->base->lcla_pool.alloc_map[idx] = d40d;
			d40d->lcla_alloc++;
			ret = i;
			break;
		}
	}

	spin_unlock_irqrestore(&d40c->base->lcla_pool.lock, flags);

	return ret;
}