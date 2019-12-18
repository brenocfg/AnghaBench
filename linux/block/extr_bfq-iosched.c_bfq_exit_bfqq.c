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
struct bfq_queue {int /*<<< orphan*/  ref; } ;
struct bfq_data {struct bfq_queue* in_service_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFQQE_BUDGET_TIMEOUT ; 
 int /*<<< orphan*/  __bfq_bfqq_expire (struct bfq_data*,struct bfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,struct bfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_put_cooperator (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_put_queue (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_schedule_dispatch (struct bfq_data*) ; 

__attribute__((used)) static void bfq_exit_bfqq(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{
	if (bfqq == bfqd->in_service_queue) {
		__bfq_bfqq_expire(bfqd, bfqq, BFQQE_BUDGET_TIMEOUT);
		bfq_schedule_dispatch(bfqd);
	}

	bfq_log_bfqq(bfqd, bfqq, "exit_bfqq: %p, %d", bfqq, bfqq->ref);

	bfq_put_cooperator(bfqq);

	bfq_put_queue(bfqq); /* release process reference */
}