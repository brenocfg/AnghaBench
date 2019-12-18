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
struct TYPE_4__ {int flush_cidx; int cidx; int size; int pidx; struct t4_swsqe* oldest_read; struct t4_swsqe* sw_sq; } ;
struct t4_wq {TYPE_2__ sq; } ;
struct t4_swsqe {int flushed; scalar_t__ opcode; } ;
struct t4_cq {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_cq; } ;
struct c4iw_qp {TYPE_1__ ibv_qp; struct t4_wq wq; } ;
struct c4iw_cq {struct t4_cq cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ FW_RI_READ_REQ ; 
 int /*<<< orphan*/  advance_oldest_read (struct t4_wq*) ; 
 int /*<<< orphan*/  insert_sq_cqe (struct t4_wq*,struct t4_cq*,struct t4_swsqe*) ; 
 struct c4iw_cq* to_c4iw_cq (int /*<<< orphan*/ ) ; 

void c4iw_flush_sq(struct c4iw_qp *qhp)
{
	unsigned short flushed = 0;
	struct t4_wq *wq = &qhp->wq;
	struct c4iw_cq *chp = to_c4iw_cq(qhp->ibv_qp.send_cq);
	struct t4_cq *cq = &chp->cq;
	int idx;
	struct t4_swsqe *swsqe;
	
	if (wq->sq.flush_cidx == -1)
		wq->sq.flush_cidx = wq->sq.cidx;
	idx = wq->sq.flush_cidx;
	BUG_ON(idx >= wq->sq.size);
	while (idx != wq->sq.pidx) {
		swsqe = &wq->sq.sw_sq[idx];
		BUG_ON(swsqe->flushed);
		swsqe->flushed = 1;
		insert_sq_cqe(wq, cq, swsqe);
		if (wq->sq.oldest_read == swsqe) {
			BUG_ON(swsqe->opcode != FW_RI_READ_REQ);
			advance_oldest_read(wq);
		}
		flushed++;
		if (++idx == wq->sq.size)
			idx = 0;
	}
	wq->sq.flush_cidx += flushed;
	if (wq->sq.flush_cidx >= wq->sq.size)
		wq->sq.flush_cidx -= wq->sq.size;
}