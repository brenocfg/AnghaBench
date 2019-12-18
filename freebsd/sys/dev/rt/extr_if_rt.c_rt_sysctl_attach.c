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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct rt_softc {int /*<<< orphan*/  tx_collision; int /*<<< orphan*/  tx_skip; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_short_err; int /*<<< orphan*/  rx_long_err; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_fifo_overflows; int /*<<< orphan*/  rx_dup_packets; int /*<<< orphan*/  rx_phy_err; int /*<<< orphan*/  rx_crc_err; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/ * tx_queue_not_empty; int /*<<< orphan*/  rx_mbuf_dmamap_errors; int /*<<< orphan*/  rx_mbuf_alloc_errors; int /*<<< orphan*/  no_tx_desc_avail; int /*<<< orphan*/  tx_defrag_packets; int /*<<< orphan*/  tx_watchdog_timeouts; int /*<<< orphan*/ * tx_data_queue_full; TYPE_1__* tx_ring; int /*<<< orphan*/  tx_delay_interrupts; int /*<<< orphan*/ * tx_interrupts; int /*<<< orphan*/  rx_delay_interrupts; int /*<<< orphan*/ * rx_interrupts; int /*<<< orphan*/  rx_coherent_interrupts; int /*<<< orphan*/  tx_coherent_interrupts; int /*<<< orphan*/  interrupts; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_queued; int /*<<< orphan*/  desc_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_ULONG (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt_sysctl_attach(struct rt_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;
	struct sysctl_oid *stats;

	ctx = device_get_sysctl_ctx(sc->dev);
	tree = device_get_sysctl_tree(sc->dev);

	/* statistic counters */
	stats = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "stats", CTLFLAG_RD, 0, "statistic");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "interrupts", CTLFLAG_RD, &sc->interrupts,
	    "all interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_coherent_interrupts", CTLFLAG_RD, &sc->tx_coherent_interrupts,
	    "Tx coherent interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_coherent_interrupts", CTLFLAG_RD, &sc->rx_coherent_interrupts,
	    "Rx coherent interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_interrupts", CTLFLAG_RD, &sc->rx_interrupts[0],
	    "Rx interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_delay_interrupts", CTLFLAG_RD, &sc->rx_delay_interrupts,
	    "Rx delay interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ3_interrupts", CTLFLAG_RD, &sc->tx_interrupts[3],
	    "Tx AC3 interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ2_interrupts", CTLFLAG_RD, &sc->tx_interrupts[2],
	    "Tx AC2 interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ1_interrupts", CTLFLAG_RD, &sc->tx_interrupts[1],
	    "Tx AC1 interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ0_interrupts", CTLFLAG_RD, &sc->tx_interrupts[0],
	    "Tx AC0 interrupts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_delay_interrupts", CTLFLAG_RD, &sc->tx_delay_interrupts,
	    "Tx delay interrupts");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ3_desc_queued", CTLFLAG_RD, &sc->tx_ring[3].desc_queued,
	    0, "Tx AC3 descriptors queued");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ3_data_queued", CTLFLAG_RD, &sc->tx_ring[3].data_queued,
	    0, "Tx AC3 data queued");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ2_desc_queued", CTLFLAG_RD, &sc->tx_ring[2].desc_queued,
	    0, "Tx AC2 descriptors queued");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ2_data_queued", CTLFLAG_RD, &sc->tx_ring[2].data_queued,
	    0, "Tx AC2 data queued");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ1_desc_queued", CTLFLAG_RD, &sc->tx_ring[1].desc_queued,
	    0, "Tx AC1 descriptors queued");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ1_data_queued", CTLFLAG_RD, &sc->tx_ring[1].data_queued,
	    0, "Tx AC1 data queued");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ0_desc_queued", CTLFLAG_RD, &sc->tx_ring[0].desc_queued,
	    0, "Tx AC0 descriptors queued");

	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ0_data_queued", CTLFLAG_RD, &sc->tx_ring[0].data_queued,
	    0, "Tx AC0 data queued");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ3_data_queue_full", CTLFLAG_RD, &sc->tx_data_queue_full[3],
	    "Tx AC3 data queue full");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ2_data_queue_full", CTLFLAG_RD, &sc->tx_data_queue_full[2],
	    "Tx AC2 data queue full");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ1_data_queue_full", CTLFLAG_RD, &sc->tx_data_queue_full[1],
	    "Tx AC1 data queue full");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "TXQ0_data_queue_full", CTLFLAG_RD, &sc->tx_data_queue_full[0],
	    "Tx AC0 data queue full");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_watchdog_timeouts", CTLFLAG_RD, &sc->tx_watchdog_timeouts,
	    "Tx watchdog timeouts");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_defrag_packets", CTLFLAG_RD, &sc->tx_defrag_packets,
	    "Tx defragmented packets");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "no_tx_desc_avail", CTLFLAG_RD, &sc->no_tx_desc_avail,
	    "no Tx descriptors available");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_mbuf_alloc_errors", CTLFLAG_RD, &sc->rx_mbuf_alloc_errors,
	    "Rx mbuf allocation errors");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_mbuf_dmamap_errors", CTLFLAG_RD, &sc->rx_mbuf_dmamap_errors,
	    "Rx mbuf DMA mapping errors");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_queue_0_not_empty", CTLFLAG_RD, &sc->tx_queue_not_empty[0],
	    "Tx queue 0 not empty");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_queue_1_not_empty", CTLFLAG_RD, &sc->tx_queue_not_empty[1],
	    "Tx queue 1 not empty");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_packets", CTLFLAG_RD, &sc->rx_packets,
	    "Rx packets");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_crc_errors", CTLFLAG_RD, &sc->rx_crc_err,
	    "Rx CRC errors");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_phy_errors", CTLFLAG_RD, &sc->rx_phy_err,
	    "Rx PHY errors");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_dup_packets", CTLFLAG_RD, &sc->rx_dup_packets,
	    "Rx duplicate packets");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_fifo_overflows", CTLFLAG_RD, &sc->rx_fifo_overflows,
	    "Rx FIFO overflows");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_bytes", CTLFLAG_RD, &sc->rx_bytes,
	    "Rx bytes");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_long_err", CTLFLAG_RD, &sc->rx_long_err,
	    "Rx too long frame errors");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "rx_short_err", CTLFLAG_RD, &sc->rx_short_err,
	    "Rx too short frame errors");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_bytes", CTLFLAG_RD, &sc->tx_bytes,
	    "Tx bytes");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_packets", CTLFLAG_RD, &sc->tx_packets,
	    "Tx packets");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_skip", CTLFLAG_RD, &sc->tx_skip,
	    "Tx skip count for GDMA ports");

	SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(stats), OID_AUTO,
	    "tx_collision", CTLFLAG_RD, &sc->tx_collision,
	    "Tx collision count for GDMA ports");
}