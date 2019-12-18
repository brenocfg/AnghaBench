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
struct TYPE_2__ {unsigned int max_depth; } ;
struct rq_wb {unsigned int wb_background; unsigned int wb_normal; TYPE_1__ rq_depth; } ;

/* Variables and functions */
 unsigned long REQ_BACKGROUND ; 
 unsigned long REQ_HIPRIO ; 
 unsigned long REQ_OP_DISCARD ; 
 unsigned long REQ_OP_MASK ; 
 unsigned int UINT_MAX ; 
 scalar_t__ close_io (struct rq_wb*) ; 
 scalar_t__ current_is_kswapd () ; 
 int /*<<< orphan*/  rwb_enabled (struct rq_wb*) ; 
 scalar_t__ wb_recent_wait (struct rq_wb*) ; 

__attribute__((used)) static inline unsigned int get_limit(struct rq_wb *rwb, unsigned long rw)
{
	unsigned int limit;

	/*
	 * If we got disabled, just return UINT_MAX. This ensures that
	 * we'll properly inc a new IO, and dec+wakeup at the end.
	 */
	if (!rwb_enabled(rwb))
		return UINT_MAX;

	if ((rw & REQ_OP_MASK) == REQ_OP_DISCARD)
		return rwb->wb_background;

	/*
	 * At this point we know it's a buffered write. If this is
	 * kswapd trying to free memory, or REQ_SYNC is set, then
	 * it's WB_SYNC_ALL writeback, and we'll use the max limit for
	 * that. If the write is marked as a background write, then use
	 * the idle limit, or go to normal if we haven't had competing
	 * IO for a bit.
	 */
	if ((rw & REQ_HIPRIO) || wb_recent_wait(rwb) || current_is_kswapd())
		limit = rwb->rq_depth.max_depth;
	else if ((rw & REQ_BACKGROUND) || close_io(rwb)) {
		/*
		 * If less than 100ms since we completed unrelated IO,
		 * limit us to half the depth for background writeback.
		 */
		limit = rwb->wb_background;
	} else
		limit = rwb->wb_normal;

	return limit;
}