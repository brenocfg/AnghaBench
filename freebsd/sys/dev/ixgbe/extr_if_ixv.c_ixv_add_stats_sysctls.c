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
struct tx_ring {int /*<<< orphan*/  total_packets; int /*<<< orphan*/  tso_tx; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct rx_ring {int /*<<< orphan*/  rx_discarded; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct ixgbevf_hw_stats {int /*<<< orphan*/  vfgotc; int /*<<< orphan*/  vfgptc; int /*<<< orphan*/  vfmprc; int /*<<< orphan*/  vfgorc; int /*<<< orphan*/  vfgprc; } ;
struct ix_tx_queue {struct tx_ring txr; } ;
struct ix_rx_queue {int /*<<< orphan*/  irqs; struct rx_ring rxr; } ;
struct TYPE_2__ {struct ixgbevf_hw_stats vf; } ;
struct adapter {int num_tx_queues; int num_rx_queues; int /*<<< orphan*/  link_irq; int /*<<< orphan*/  watchdog_events; TYPE_1__ stats; struct ix_rx_queue* rx_queues; struct ix_tx_queue* tx_queues; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int QUEUE_NAME_LEN ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_ULONG (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
ixv_add_stats_sysctls(struct adapter *adapter)
{
	device_t                dev = adapter->dev;
	struct ix_tx_queue      *tx_que = adapter->tx_queues;
	struct ix_rx_queue      *rx_que = adapter->rx_queues;
	struct sysctl_ctx_list  *ctx = device_get_sysctl_ctx(dev);
	struct sysctl_oid       *tree = device_get_sysctl_tree(dev);
	struct sysctl_oid_list  *child = SYSCTL_CHILDREN(tree);
	struct ixgbevf_hw_stats *stats = &adapter->stats.vf;
	struct sysctl_oid       *stat_node, *queue_node;
	struct sysctl_oid_list  *stat_list, *queue_list;

#define QUEUE_NAME_LEN 32
	char                    namebuf[QUEUE_NAME_LEN];

	/* Driver Statistics */
	SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "watchdog_events",
	    CTLFLAG_RD, &adapter->watchdog_events, "Watchdog timeouts");
	SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "link_irq",
	    CTLFLAG_RD, &adapter->link_irq, "Link MSI-X IRQ Handled");

	for (int i = 0; i < adapter->num_tx_queues; i++, tx_que++) {
		struct tx_ring *txr = &tx_que->txr;
		snprintf(namebuf, QUEUE_NAME_LEN, "queue%d", i);
		queue_node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, namebuf,
		    CTLFLAG_RD, NULL, "Queue Name");
		queue_list = SYSCTL_CHILDREN(queue_node);

		SYSCTL_ADD_UQUAD(ctx, queue_list, OID_AUTO, "tso_tx",
		    CTLFLAG_RD, &(txr->tso_tx), "TSO Packets");
		SYSCTL_ADD_UQUAD(ctx, queue_list, OID_AUTO, "tx_packets",
		    CTLFLAG_RD, &(txr->total_packets), "TX Packets");
	}

	for (int i = 0; i < adapter->num_rx_queues; i++, rx_que++) {
		struct rx_ring *rxr = &rx_que->rxr;
		snprintf(namebuf, QUEUE_NAME_LEN, "queue%d", i);
		queue_node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, namebuf,
		    CTLFLAG_RD, NULL, "Queue Name");
		queue_list = SYSCTL_CHILDREN(queue_node);

		SYSCTL_ADD_UQUAD(ctx, queue_list, OID_AUTO, "irqs",
		    CTLFLAG_RD, &(rx_que->irqs), "IRQs on queue");
		SYSCTL_ADD_UQUAD(ctx, queue_list, OID_AUTO, "rx_packets",
		    CTLFLAG_RD, &(rxr->rx_packets), "RX packets");
		SYSCTL_ADD_UQUAD(ctx, queue_list, OID_AUTO, "rx_bytes",
		    CTLFLAG_RD, &(rxr->rx_bytes), "RX bytes");
		SYSCTL_ADD_UQUAD(ctx, queue_list, OID_AUTO, "rx_discarded",
		    CTLFLAG_RD, &(rxr->rx_discarded), "Discarded RX packets");
	}

	stat_node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "mac",
	    CTLFLAG_RD, NULL, "VF Statistics (read from HW registers)");
	stat_list = SYSCTL_CHILDREN(stat_node);

	SYSCTL_ADD_UQUAD(ctx, stat_list, OID_AUTO, "good_pkts_rcvd",
	    CTLFLAG_RD, &stats->vfgprc, "Good Packets Received");
	SYSCTL_ADD_UQUAD(ctx, stat_list, OID_AUTO, "good_octets_rcvd",
	    CTLFLAG_RD, &stats->vfgorc, "Good Octets Received");
	SYSCTL_ADD_UQUAD(ctx, stat_list, OID_AUTO, "mcast_pkts_rcvd",
	    CTLFLAG_RD, &stats->vfmprc, "Multicast Packets Received");
	SYSCTL_ADD_UQUAD(ctx, stat_list, OID_AUTO, "good_pkts_txd",
	    CTLFLAG_RD, &stats->vfgptc, "Good Packets Transmitted");
	SYSCTL_ADD_UQUAD(ctx, stat_list, OID_AUTO, "good_octets_txd",
	    CTLFLAG_RD, &stats->vfgotc, "Good Octets Transmitted");
}