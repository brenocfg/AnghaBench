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
struct TYPE_6__ {scalar_t__ in_use; scalar_t__ cidx; scalar_t__ size; scalar_t__ pidx; TYPE_2__* queue; int /*<<< orphan*/  msn; } ;
struct t4_wq {TYPE_3__ rq; int /*<<< orphan*/  error; } ;
struct TYPE_4__ {scalar_t__ host_cidx; } ;
struct TYPE_5__ {TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void t4_rq_consume(struct t4_wq *wq)
{
	wq->rq.in_use--;
	wq->rq.msn++;
	if (++wq->rq.cidx == wq->rq.size)
		wq->rq.cidx = 0;
	assert((wq->rq.cidx != wq->rq.pidx) || wq->rq.in_use == 0);
	if (!wq->error)
		wq->rq.queue[wq->rq.size].status.host_cidx = wq->rq.cidx;
}