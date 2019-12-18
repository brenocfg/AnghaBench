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
struct ena_que {int /*<<< orphan*/  cleanup_tq; int /*<<< orphan*/  cleanup_task; } ;
struct ena_adapter {int num_queues; struct ena_que* que; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_destroy_all_rx_queues (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_destroy_all_tx_queues (struct ena_adapter*) ; 
 scalar_t__ taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_destroy_all_io_queues(struct ena_adapter *adapter)
{
	struct ena_que *queue;
	int i;

	for (i = 0; i < adapter->num_queues; i++) {
		queue = &adapter->que[i];
		while (taskqueue_cancel(queue->cleanup_tq,
		    &queue->cleanup_task, NULL))
			taskqueue_drain(queue->cleanup_tq,
			    &queue->cleanup_task);
		taskqueue_free(queue->cleanup_tq);
	}

	ena_destroy_all_tx_queues(adapter);
	ena_destroy_all_rx_queues(adapter);
}