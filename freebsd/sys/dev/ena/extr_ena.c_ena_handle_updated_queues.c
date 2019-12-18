#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ena_com_dev_get_features_ctx {int dummy; } ;
struct ena_com_dev {int dummy; } ;
struct ena_calc_queue_size_ctx {scalar_t__ tx_queue_size; scalar_t__ rx_queue_size; int /*<<< orphan*/  max_rx_sgl_size; int /*<<< orphan*/  max_tx_sgl_size; int /*<<< orphan*/  pdev; struct ena_com_dev_get_features_ctx* get_feat_ctx; struct ena_com_dev* ena_dev; int /*<<< orphan*/  member_0; } ;
struct ena_adapter {scalar_t__ buf_ring_size; scalar_t__ tx_ring_size; scalar_t__ rx_ring_size; int num_queues; int /*<<< orphan*/  max_rx_sgl_size; int /*<<< orphan*/  max_tx_sgl_size; TYPE_1__* tx_ring; int /*<<< orphan*/  pdev; struct ena_com_dev* ena_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ buf_ring_size; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_RSS_ACTIVE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int ena_calc_io_queue_num (struct ena_adapter*,struct ena_com_dev_get_features_ctx*) ; 
 int ena_calc_queue_size (struct ena_adapter*,struct ena_calc_queue_size_ctx*) ; 
 int /*<<< orphan*/  ena_com_rss_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_free_all_io_rings_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_init_io_rings (struct ena_adapter*) ; 
 int ena_rss_init_default (struct ena_adapter*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_handle_updated_queues(struct ena_adapter *adapter,
    struct ena_com_dev_get_features_ctx *get_feat_ctx)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	struct ena_calc_queue_size_ctx calc_queue_ctx = { 0 };
	device_t pdev = adapter->pdev;
	bool are_queues_changed = false;
	int io_queue_num, rc;

	calc_queue_ctx.ena_dev = ena_dev;
	calc_queue_ctx.get_feat_ctx = get_feat_ctx;
	calc_queue_ctx.pdev = pdev;

	io_queue_num = ena_calc_io_queue_num(adapter, get_feat_ctx);
	rc = ena_calc_queue_size(adapter, &calc_queue_ctx);
	if (unlikely(rc != 0 || io_queue_num <= 0))
		return EFAULT;

	if (adapter->tx_ring->buf_ring_size != adapter->buf_ring_size)
		are_queues_changed = true;

	if (unlikely(adapter->tx_ring_size > calc_queue_ctx.tx_queue_size ||
	    adapter->rx_ring_size > calc_queue_ctx.rx_queue_size)) {
		device_printf(pdev,
		    "Not enough resources to allocate requested queue sizes "
		    "(TX,RX)=(%d,%d), falling back to queue sizes "
		    "(TX,RX)=(%d,%d)\n",
		    adapter->tx_ring_size,
		    adapter->rx_ring_size,
		    calc_queue_ctx.tx_queue_size,
		    calc_queue_ctx.rx_queue_size);
		adapter->tx_ring_size = calc_queue_ctx.tx_queue_size;
		adapter->rx_ring_size = calc_queue_ctx.rx_queue_size;
		adapter->max_tx_sgl_size = calc_queue_ctx.max_tx_sgl_size;
		adapter->max_rx_sgl_size = calc_queue_ctx.max_rx_sgl_size;
		are_queues_changed = true;
	}

	if (unlikely(adapter->num_queues > io_queue_num)) {
		device_printf(pdev,
		    "Not enough resources to allocate %d queues, "
		    "falling back to %d queues\n",
		    adapter->num_queues, io_queue_num);
		adapter->num_queues = io_queue_num;
		if (ENA_FLAG_ISSET(ENA_FLAG_RSS_ACTIVE, adapter)) {
			ena_com_rss_destroy(ena_dev);
			rc = ena_rss_init_default(adapter);
			if (unlikely(rc != 0) && (rc != EOPNOTSUPP)) {
				device_printf(pdev, "Cannot init RSS rc: %d\n",
				    rc);
				return (rc);
			}
		}
		are_queues_changed = true;
	}

	if (unlikely(are_queues_changed)) {
		ena_free_all_io_rings_resources(adapter);
		ena_init_io_rings(adapter);
	}

	return (0);
}