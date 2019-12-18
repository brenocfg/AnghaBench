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
struct bus_dma_tag_common {TYPE_1__* impl; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_lock_t ;
typedef  int /*<<< orphan*/  bus_dma_filter_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int (* tag_create ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ **) ;} ;
struct TYPE_3__ {int (* tag_create ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 TYPE_2__ bus_dma_bounce_impl ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ **) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ **) ; 

int
bus_dma_tag_create(bus_dma_tag_t parent, bus_size_t alignment,
    bus_addr_t boundary, bus_addr_t lowaddr, bus_addr_t highaddr,
    bus_dma_filter_t *filter, void *filterarg, bus_size_t maxsize,
    int nsegments, bus_size_t maxsegsz, int flags, bus_dma_lock_t *lockfunc,
    void *lockfuncarg, bus_dma_tag_t *dmat)
{
	struct bus_dma_tag_common *tc;
	int error;

	if (parent == NULL) {
		error = bus_dma_bounce_impl.tag_create(parent, alignment,
		    boundary, lowaddr, highaddr, filter, filterarg, maxsize,
		    nsegments, maxsegsz, flags, lockfunc, lockfuncarg, dmat);
	} else {
		tc = (struct bus_dma_tag_common *)parent;
		error = tc->impl->tag_create(parent, alignment,
		    boundary, lowaddr, highaddr, filter, filterarg, maxsize,
		    nsegments, maxsegsz, flags, lockfunc, lockfuncarg, dmat);
	}
	return (error);
}