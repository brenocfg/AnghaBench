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
struct bfq_queue {struct request* next_rq; } ;
struct bfq_data {int wait_dispatch; struct bfq_queue* in_service_queue; int /*<<< orphan*/  queue; struct request* waited_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFQQE_BUDGET_EXHAUSTED ; 
 int /*<<< orphan*/  bfq_bfqq_expire (struct bfq_data*,struct bfq_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_bfqq_served (struct bfq_queue*,unsigned long) ; 
 scalar_t__ bfq_class_idle (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_dispatch_remove (int /*<<< orphan*/ ,struct request*) ; 
 unsigned long bfq_serv_to_charge (struct request*,struct bfq_queue*) ; 
 int bfq_tot_busy_queues (struct bfq_data*) ; 
 int /*<<< orphan*/  bfq_update_wr_data (struct bfq_data*,struct bfq_queue*) ; 

__attribute__((used)) static struct request *bfq_dispatch_rq_from_bfqq(struct bfq_data *bfqd,
						 struct bfq_queue *bfqq)
{
	struct request *rq = bfqq->next_rq;
	unsigned long service_to_charge;

	service_to_charge = bfq_serv_to_charge(rq, bfqq);

	bfq_bfqq_served(bfqq, service_to_charge);

	if (bfqq == bfqd->in_service_queue && bfqd->wait_dispatch) {
		bfqd->wait_dispatch = false;
		bfqd->waited_rq = rq;
	}

	bfq_dispatch_remove(bfqd->queue, rq);

	if (bfqq != bfqd->in_service_queue)
		goto return_rq;

	/*
	 * If weight raising has to terminate for bfqq, then next
	 * function causes an immediate update of bfqq's weight,
	 * without waiting for next activation. As a consequence, on
	 * expiration, bfqq will be timestamped as if has never been
	 * weight-raised during this service slot, even if it has
	 * received part or even most of the service as a
	 * weight-raised queue. This inflates bfqq's timestamps, which
	 * is beneficial, as bfqq is then more willing to leave the
	 * device immediately to possible other weight-raised queues.
	 */
	bfq_update_wr_data(bfqd, bfqq);

	/*
	 * Expire bfqq, pretending that its budget expired, if bfqq
	 * belongs to CLASS_IDLE and other queues are waiting for
	 * service.
	 */
	if (!(bfq_tot_busy_queues(bfqd) > 1 && bfq_class_idle(bfqq)))
		goto return_rq;

	bfq_bfqq_expire(bfqd, bfqq, false, BFQQE_BUDGET_EXHAUSTED);

return_rq:
	return rq;
}