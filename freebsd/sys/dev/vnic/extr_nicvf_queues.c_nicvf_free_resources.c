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
struct queue_set {int rbdr_cnt; int cq_cnt; int sq_cnt; int /*<<< orphan*/ * sq; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * rbdr; int /*<<< orphan*/ * qs_err_taskq; int /*<<< orphan*/  qs_err_task; } ;
struct nicvf {struct queue_set* qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nicvf_free_cmp_queue (struct nicvf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nicvf_free_rbdr (struct nicvf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nicvf_free_snd_queue (struct nicvf*,int /*<<< orphan*/ *) ; 
 scalar_t__ taskqueue_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nicvf_free_resources(struct nicvf *nic)
{
	int qidx;
	struct queue_set *qs;

	qs = nic->qs;
	/*
	 * Remove QS error task first since it has to be dead
	 * to safely free completion queue tasks.
	 */
	if (qs->qs_err_taskq != NULL) {
		/* Shut down QS error tasks */
		while (taskqueue_cancel(qs->qs_err_taskq,
		    &qs->qs_err_task,  NULL) != 0) {
			taskqueue_drain(qs->qs_err_taskq, &qs->qs_err_task);

		}
		taskqueue_free(qs->qs_err_taskq);
		qs->qs_err_taskq = NULL;
	}
	/* Free receive buffer descriptor ring */
	for (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
		nicvf_free_rbdr(nic, &qs->rbdr[qidx]);

	/* Free completion queue */
	for (qidx = 0; qidx < qs->cq_cnt; qidx++)
		nicvf_free_cmp_queue(nic, &qs->cq[qidx]);

	/* Free send queue */
	for (qidx = 0; qidx < qs->sq_cnt; qidx++)
		nicvf_free_snd_queue(nic, &qs->sq[qidx]);
}