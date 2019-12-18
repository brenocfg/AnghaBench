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
struct TYPE_6__ {int in_use; scalar_t__ cidx; scalar_t__ flush_cidx; scalar_t__ size; scalar_t__ pidx; TYPE_2__* queue; } ;
struct t4_wq {TYPE_3__ sq; int /*<<< orphan*/  error; } ;
struct TYPE_4__ {scalar_t__ host_cidx; } ;
struct TYPE_5__ {TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void t4_sq_consume(struct t4_wq *wq)
{
	assert(wq->sq.in_use >= 1);
	if (wq->sq.cidx == wq->sq.flush_cidx)
                wq->sq.flush_cidx = -1;
	wq->sq.in_use--;
	if (++wq->sq.cidx == wq->sq.size)
		wq->sq.cidx = 0;
	assert((wq->sq.cidx != wq->sq.pidx) || wq->sq.in_use == 0);
	if (!wq->error){
		/* This write is only for debugging, the value does not matter
		 * for DMA */
		wq->sq.queue[wq->sq.size].status.host_cidx = wq->sq.cidx;
	}
}