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
struct rbdr {int /*<<< orphan*/  rbdr_task_nowait; int /*<<< orphan*/  rbdr_taskq; } ;
struct queue_set {int rbdr_cnt; struct rbdr* rbdr; } ;
struct nicvf {struct queue_set* qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_INTR_RBDR ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_is_intr_enabled (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nicvf_rbdr_intr_handler(void *arg)
{
	struct nicvf *nic;
	struct queue_set *qs;
	struct rbdr *rbdr;
	int qidx;

	nic = (struct nicvf *)arg;

	/* Disable RBDR interrupt and schedule softirq */
	for (qidx = 0; qidx < nic->qs->rbdr_cnt; qidx++) {
		if (!nicvf_is_intr_enabled(nic, NICVF_INTR_RBDR, qidx))
			continue;
		nicvf_disable_intr(nic, NICVF_INTR_RBDR, qidx);

		qs = nic->qs;
		rbdr = &qs->rbdr[qidx];
		taskqueue_enqueue(rbdr->rbdr_taskq, &rbdr->rbdr_task_nowait);
		/* Clear interrupt */
		nicvf_clear_intr(nic, NICVF_INTR_RBDR, qidx);
	}
}