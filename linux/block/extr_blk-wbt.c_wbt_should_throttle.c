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
struct rq_wb {int dummy; } ;
struct bio {int bi_opf; } ;

/* Variables and functions */
 int REQ_IDLE ; 
#define  REQ_OP_DISCARD 129 
#define  REQ_OP_WRITE 128 
 int REQ_SYNC ; 
 int bio_op (struct bio*) ; 

__attribute__((used)) static inline bool wbt_should_throttle(struct rq_wb *rwb, struct bio *bio)
{
	switch (bio_op(bio)) {
	case REQ_OP_WRITE:
		/*
		 * Don't throttle WRITE_ODIRECT
		 */
		if ((bio->bi_opf & (REQ_SYNC | REQ_IDLE)) ==
		    (REQ_SYNC | REQ_IDLE))
			return false;
		/* fallthrough */
	case REQ_OP_DISCARD:
		return true;
	default:
		return false;
	}
}