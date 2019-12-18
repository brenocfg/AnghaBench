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
struct nicvf {int dummy; } ;
struct cmp_queue {int /*<<< orphan*/  idx; int /*<<< orphan*/  cmp_task; int /*<<< orphan*/  cmp_taskq; struct nicvf* nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_INTR_CQ ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nicvf_cq_intr_handler (struct nicvf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nicvf_cmp_task(void *arg, int pending)
{
	struct cmp_queue *cq;
	struct nicvf *nic;
	int cmp_err;

	cq = (struct cmp_queue *)arg;
	nic = cq->nic;

	/* Handle CQ descriptors */
	cmp_err = nicvf_cq_intr_handler(nic, cq->idx);
	if (__predict_false(cmp_err != 0)) {
		/*
		 * Schedule another thread here since we did not
		 * process the entire CQ due to Tx or Rx CQ parse error.
		 */
		taskqueue_enqueue(cq->cmp_taskq, &cq->cmp_task);

	}

	nicvf_clear_intr(nic, NICVF_INTR_CQ, cq->idx);
	/* Reenable interrupt (previously disabled in nicvf_intr_handler() */
	nicvf_enable_intr(nic, NICVF_INTR_CQ, cq->idx);

}