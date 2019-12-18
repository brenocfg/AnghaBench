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
typedef  int u8 ;
struct TYPE_6__ {int pidx; int size; int wq_pidx; TYPE_2__* queue; int /*<<< orphan*/  in_use; } ;
struct t4_wq {TYPE_3__ rq; int /*<<< orphan*/  error; } ;
struct TYPE_4__ {int host_pidx; } ;
struct TYPE_5__ {TYPE_1__ status; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T4_EQ_ENTRY_SIZE ; 
 int T4_RQ_NUM_SLOTS ; 

__attribute__((used)) static inline void t4_rq_produce(struct t4_wq *wq, u8 len16)
{
	wq->rq.in_use++;
	if (++wq->rq.pidx == wq->rq.size)
		wq->rq.pidx = 0;
	wq->rq.wq_pidx += DIV_ROUND_UP(len16*16, T4_EQ_ENTRY_SIZE);
	if (wq->rq.wq_pidx >= wq->rq.size * T4_RQ_NUM_SLOTS)
		wq->rq.wq_pidx %= wq->rq.size * T4_RQ_NUM_SLOTS;
	if (!wq->error)
		wq->rq.queue[wq->rq.size].status.host_pidx = wq->rq.pidx;
}