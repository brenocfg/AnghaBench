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
struct bio {int dummy; } ;
struct bfq_queue {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ioc; } ;
struct bfq_io_cq {int ioprio; TYPE_2__ icq; } ;
struct bfq_data {int dummy; } ;
struct TYPE_3__ {int ioprio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 struct bfq_queue* bfq_get_queue (struct bfq_data*,struct bio*,int /*<<< orphan*/ ,struct bfq_io_cq*) ; 
 int /*<<< orphan*/  bfq_put_queue (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_set_next_ioprio_data (struct bfq_queue*,struct bfq_io_cq*) ; 
 int /*<<< orphan*/  bic_set_bfqq (struct bfq_io_cq*,struct bfq_queue*,int) ; 
 struct bfq_data* bic_to_bfqd (struct bfq_io_cq*) ; 
 struct bfq_queue* bic_to_bfqq (struct bfq_io_cq*,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bfq_check_ioprio_change(struct bfq_io_cq *bic, struct bio *bio)
{
	struct bfq_data *bfqd = bic_to_bfqd(bic);
	struct bfq_queue *bfqq;
	int ioprio = bic->icq.ioc->ioprio;

	/*
	 * This condition may trigger on a newly created bic, be sure to
	 * drop the lock before returning.
	 */
	if (unlikely(!bfqd) || likely(bic->ioprio == ioprio))
		return;

	bic->ioprio = ioprio;

	bfqq = bic_to_bfqq(bic, false);
	if (bfqq) {
		/* release process reference on this queue */
		bfq_put_queue(bfqq);
		bfqq = bfq_get_queue(bfqd, bio, BLK_RW_ASYNC, bic);
		bic_set_bfqq(bic, bfqq, false);
	}

	bfqq = bic_to_bfqq(bic, true);
	if (bfqq)
		bfq_set_next_ioprio_data(bfqq, bic);
}