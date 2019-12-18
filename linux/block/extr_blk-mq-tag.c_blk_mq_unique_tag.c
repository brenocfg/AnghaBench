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
typedef  int u32 ;
struct request {int tag; TYPE_1__* mq_hctx; } ;
struct TYPE_2__ {int queue_num; } ;

/* Variables and functions */
 int BLK_MQ_UNIQUE_TAG_BITS ; 
 int BLK_MQ_UNIQUE_TAG_MASK ; 

u32 blk_mq_unique_tag(struct request *rq)
{
	return (rq->mq_hctx->queue_num << BLK_MQ_UNIQUE_TAG_BITS) |
		(rq->tag & BLK_MQ_UNIQUE_TAG_MASK);
}