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
struct queue_set {int /*<<< orphan*/  qs_err_task; int /*<<< orphan*/  qs_err_taskq; } ;
struct nicvf {struct queue_set* qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_INTR_QS_ERR ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nicvf_qs_err_intr_handler(void *arg)
{
	struct nicvf *nic = (struct nicvf *)arg;
	struct queue_set *qs = nic->qs;

	/* Disable Qset err interrupt and schedule softirq */
	nicvf_disable_intr(nic, NICVF_INTR_QS_ERR, 0);
	taskqueue_enqueue(qs->qs_err_taskq, &qs->qs_err_task);
	nicvf_clear_intr(nic, NICVF_INTR_QS_ERR, 0);

}