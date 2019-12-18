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
struct request {int rq_flags; TYPE_1__* q; } ;
struct TYPE_2__ {scalar_t__ elevator; } ;

/* Variables and functions */
 int RQF_IO_STAT ; 
 int RQF_STATS ; 

__attribute__((used)) static inline bool blk_mq_need_time_stamp(struct request *rq)
{
	return (rq->rq_flags & (RQF_IO_STAT | RQF_STATS)) || rq->q->elevator;
}