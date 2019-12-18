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
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct ena_ring {int /*<<< orphan*/  ena_com_io_cq; int /*<<< orphan*/  ena_com_io_sq; } ;
struct ena_que {int /*<<< orphan*/  cleanup_tq; int /*<<< orphan*/  cleanup_task; } ;
struct ena_com_dev {int /*<<< orphan*/  tx_mem_queue_type; } ;
struct ena_com_create_io_ctx {void* qid; void* msix_vector; int /*<<< orphan*/  queue_size; int /*<<< orphan*/  direction; int /*<<< orphan*/  mem_queue_type; } ;
struct ena_adapter {int num_queues; int /*<<< orphan*/  pdev; struct ena_que* que; struct ena_ring* rx_ring; int /*<<< orphan*/  rx_ring_size; struct ena_ring* tx_ring; int /*<<< orphan*/  tx_ring_size; struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int /*<<< orphan*/  ENA_COM_IO_QUEUE_DIRECTION_RX ; 
 int /*<<< orphan*/  ENA_COM_IO_QUEUE_DIRECTION_TX ; 
 void* ENA_IO_IRQ_IDX (int) ; 
 void* ENA_IO_RXQ_IDX (int) ; 
 void* ENA_IO_TXQ_IDX (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ena_que*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ena_cleanup ; 
 int ena_com_create_io_queue (struct ena_com_dev*,struct ena_com_create_io_ctx*) ; 
 int /*<<< orphan*/  ena_com_destroy_io_queue (struct ena_com_dev*,void*) ; 
 int ena_com_get_io_handlers (struct ena_com_dev*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_create_io_queues(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	struct ena_com_create_io_ctx ctx;
	struct ena_ring *ring;
	struct ena_que *queue;
	uint16_t ena_qid;
	uint32_t msix_vector;
	int rc, i;

	/* Create TX queues */
	for (i = 0; i < adapter->num_queues; i++) {
		msix_vector = ENA_IO_IRQ_IDX(i);
		ena_qid = ENA_IO_TXQ_IDX(i);
		ctx.mem_queue_type = ena_dev->tx_mem_queue_type;
		ctx.direction = ENA_COM_IO_QUEUE_DIRECTION_TX;
		ctx.queue_size = adapter->tx_ring_size;
		ctx.msix_vector = msix_vector;
		ctx.qid = ena_qid;
		rc = ena_com_create_io_queue(ena_dev, &ctx);
		if (rc != 0) {
			device_printf(adapter->pdev,
			    "Failed to create io TX queue #%d rc: %d\n", i, rc);
			goto err_tx;
		}
		ring = &adapter->tx_ring[i];
		rc = ena_com_get_io_handlers(ena_dev, ena_qid,
		    &ring->ena_com_io_sq,
		    &ring->ena_com_io_cq);
		if (rc != 0) {
			device_printf(adapter->pdev,
			    "Failed to get TX queue handlers. TX queue num"
			    " %d rc: %d\n", i, rc);
			ena_com_destroy_io_queue(ena_dev, ena_qid);
			goto err_tx;
		}
	}

	/* Create RX queues */
	for (i = 0; i < adapter->num_queues; i++) {
		msix_vector = ENA_IO_IRQ_IDX(i);
		ena_qid = ENA_IO_RXQ_IDX(i);
		ctx.mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
		ctx.direction = ENA_COM_IO_QUEUE_DIRECTION_RX;
		ctx.queue_size = adapter->rx_ring_size;
		ctx.msix_vector = msix_vector;
		ctx.qid = ena_qid;
		rc = ena_com_create_io_queue(ena_dev, &ctx);
		if (unlikely(rc != 0)) {
			device_printf(adapter->pdev,
			    "Failed to create io RX queue[%d] rc: %d\n", i, rc);
			goto err_rx;
		}

		ring = &adapter->rx_ring[i];
		rc = ena_com_get_io_handlers(ena_dev, ena_qid,
		    &ring->ena_com_io_sq,
		    &ring->ena_com_io_cq);
		if (unlikely(rc != 0)) {
			device_printf(adapter->pdev,
			    "Failed to get RX queue handlers. RX queue num"
			    " %d rc: %d\n", i, rc);
			ena_com_destroy_io_queue(ena_dev, ena_qid);
			goto err_rx;
		}
	}

	for (i = 0; i < adapter->num_queues; i++) {
		queue = &adapter->que[i];

		TASK_INIT(&queue->cleanup_task, 0, ena_cleanup, queue);
		queue->cleanup_tq = taskqueue_create_fast("ena cleanup",
		    M_WAITOK, taskqueue_thread_enqueue, &queue->cleanup_tq);

		taskqueue_start_threads(&queue->cleanup_tq, 1, PI_NET,
		    "%s queue %d cleanup",
		    device_get_nameunit(adapter->pdev), i);
	}

	return (0);

err_rx:
	while (i--)
		ena_com_destroy_io_queue(ena_dev, ENA_IO_RXQ_IDX(i));
	i = adapter->num_queues;
err_tx:
	while (i--)
		ena_com_destroy_io_queue(ena_dev, ENA_IO_TXQ_IDX(i));

	return (ENXIO);
}