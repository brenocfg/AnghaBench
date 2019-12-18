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
struct request {int dummy; } ;
struct bfq_queue {int seek_history; int wr_coeff; scalar_t__ wr_cur_max_time; int /*<<< orphan*/  last_request_pos; } ;
struct bfq_data {scalar_t__ bfq_wr_rt_max_time; } ;

/* Variables and functions */
 scalar_t__ BFQQ_TOTALLY_SEEKY (struct bfq_queue*) ; 
 int BFQ_RQ_SEEKY (struct bfq_data*,int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  bfq_bfqq_end_wr (struct bfq_queue*) ; 

__attribute__((used)) static void
bfq_update_io_seektime(struct bfq_data *bfqd, struct bfq_queue *bfqq,
		       struct request *rq)
{
	bfqq->seek_history <<= 1;
	bfqq->seek_history |= BFQ_RQ_SEEKY(bfqd, bfqq->last_request_pos, rq);

	if (bfqq->wr_coeff > 1 &&
	    bfqq->wr_cur_max_time == bfqd->bfq_wr_rt_max_time &&
	    BFQQ_TOTALLY_SEEKY(bfqq))
		bfq_bfqq_end_wr(bfqq);
}