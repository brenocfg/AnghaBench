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
struct request {TYPE_1__* mq_ctx; } ;
struct TYPE_2__ {unsigned int cpu; } ;

/* Variables and functions */

unsigned int blk_mq_rq_cpu(struct request *rq)
{
	return rq->mq_ctx->cpu;
}