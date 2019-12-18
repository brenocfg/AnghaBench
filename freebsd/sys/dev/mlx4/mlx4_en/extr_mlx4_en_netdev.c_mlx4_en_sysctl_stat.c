#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct mlx4_en_tx_ring {int /*<<< orphan*/  defrag_attempts; int /*<<< orphan*/  tso_packets; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct mlx4_en_rx_ring {int /*<<< orphan*/  errors; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_gt_1548_bytes_packets; int /*<<< orphan*/  tx_1548_bytes_packets; int /*<<< orphan*/  tx_1522_bytes_packets; int /*<<< orphan*/  tx_1518_bytes_packets; int /*<<< orphan*/  tx_1023_bytes_packets; int /*<<< orphan*/  tx_511_bytes_packets; int /*<<< orphan*/  tx_255_bytes_packets; int /*<<< orphan*/  tx_127_bytes_packets; int /*<<< orphan*/  tx_lt_64_bytes_packets; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_broadcast_packets; int /*<<< orphan*/  tx_multicast_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_gt_1548_bytes_packets; int /*<<< orphan*/  rx_1548_bytes_packets; int /*<<< orphan*/  rx_1522_bytes_packets; int /*<<< orphan*/  rx_1518_bytes_packets; int /*<<< orphan*/  rx_1023_bytes_packets; int /*<<< orphan*/  rx_511_bytes_packets; int /*<<< orphan*/  rx_255_bytes_packets; int /*<<< orphan*/  rx_127_bytes_packets; int /*<<< orphan*/  rx_lt_64_bytes_packets; int /*<<< orphan*/  rx_out_range_length_error; int /*<<< orphan*/  rx_in_range_length_error; int /*<<< orphan*/  rx_jabbers; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_broadcast_packets; int /*<<< orphan*/  rx_multicast_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  defrag_attempts; int /*<<< orphan*/  tx_chksum_offload; int /*<<< orphan*/  rx_chksum_none; int /*<<< orphan*/  rx_chksum_good; int /*<<< orphan*/  rx_alloc_failed; int /*<<< orphan*/  oversized_packets; int /*<<< orphan*/  tx_timeout; int /*<<< orphan*/  wake_queue; int /*<<< orphan*/  queue_stopped; int /*<<< orphan*/  tso_packets; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_coal_avg; int /*<<< orphan*/  tx_coal_avg; int /*<<< orphan*/  inflight_avg; int /*<<< orphan*/  tx_pktsz_avg; int /*<<< orphan*/  tx_poll; } ;
struct mlx4_en_priv {int tx_ring_num; int rx_ring_num; struct mlx4_en_rx_ring** rx_ring; struct mlx4_en_tx_ring** tx_ring; TYPE_3__ pkstats; TYPE_2__ port_stats; TYPE_1__ pstats; struct sysctl_oid* stat_sysctl; struct sysctl_oid* conf_sysctl; struct sysctl_ctx_list stat_ctx; } ;
typedef  int /*<<< orphan*/  namebuf ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 void* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sysctl_ctx_init (struct sysctl_ctx_list*) ; 

__attribute__((used)) static void mlx4_en_sysctl_stat(struct mlx4_en_priv *priv)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *node_list;
	struct sysctl_oid *ring_node;
	struct sysctl_oid_list *ring_list;
	struct mlx4_en_tx_ring *tx_ring;
	struct mlx4_en_rx_ring *rx_ring;
	char namebuf[128];
	int i;

	ctx = &priv->stat_ctx;
	sysctl_ctx_init(ctx);
	priv->stat_sysctl = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(priv->conf_sysctl), OID_AUTO,
	    "stat", CTLFLAG_RD, NULL, "Statistics");
	node_list = SYSCTL_CHILDREN(priv->stat_sysctl);

#ifdef MLX4_EN_PERF_STAT
	SYSCTL_ADD_UINT(ctx, node_list, OID_AUTO, "tx_poll", CTLFLAG_RD,
	    &priv->pstats.tx_poll, "TX Poll calls");
	SYSCTL_ADD_QUAD(ctx, node_list, OID_AUTO, "tx_pktsz_avg", CTLFLAG_RD,
	    &priv->pstats.tx_pktsz_avg, "TX average packet size");
	SYSCTL_ADD_UINT(ctx, node_list, OID_AUTO, "inflight_avg", CTLFLAG_RD,
	    &priv->pstats.inflight_avg, "TX average packets in-flight");
	SYSCTL_ADD_UINT(ctx, node_list, OID_AUTO, "tx_coal_avg", CTLFLAG_RD,
	    &priv->pstats.tx_coal_avg, "TX average coalesced completions");
	SYSCTL_ADD_UINT(ctx, node_list, OID_AUTO, "rx_coal_avg", CTLFLAG_RD,
	    &priv->pstats.rx_coal_avg, "RX average coalesced completions");
#endif

	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tso_packets", CTLFLAG_RD,
	    &priv->port_stats.tso_packets, 0, "TSO packets sent");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "queue_stopped", CTLFLAG_RD,
	    &priv->port_stats.queue_stopped, 0, "Queue full");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "wake_queue", CTLFLAG_RD,
	    &priv->port_stats.wake_queue, 0, "Queue resumed after full");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_timeout", CTLFLAG_RD,
	    &priv->port_stats.tx_timeout, 0, "Transmit timeouts");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_oversized_packets", CTLFLAG_RD,
	    &priv->port_stats.oversized_packets, 0, "TX oversized packets, m_defrag failed");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_alloc_failed", CTLFLAG_RD,
	    &priv->port_stats.rx_alloc_failed, 0, "RX failed to allocate mbuf");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_chksum_good", CTLFLAG_RD,
            &priv->port_stats.rx_chksum_good, 0, "RX checksum offload success");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_chksum_none", CTLFLAG_RD,
	    &priv->port_stats.rx_chksum_none, 0, "RX without checksum offload");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_chksum_offload",
	    CTLFLAG_RD, &priv->port_stats.tx_chksum_offload, 0,
	    "TX checksum offloads");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "defrag_attempts",
	    CTLFLAG_RD, &priv->port_stats.defrag_attempts, 0,
	    "Oversized chains defragged");

	/* Could strdup the names and add in a loop.  This is simpler. */
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_bytes", CTLFLAG_RD,
	    &priv->pkstats.rx_bytes, 0, "RX Bytes");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_packets, 0, "RX packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_multicast_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_multicast_packets, 0, "RX Multicast Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_broadcast_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_broadcast_packets, 0, "RX Broadcast Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_errors", CTLFLAG_RD,
	    &priv->pkstats.rx_errors, 0, "RX Errors");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_dropped", CTLFLAG_RD,
	    &priv->pkstats.rx_dropped, 0, "RX Dropped");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_length_errors", CTLFLAG_RD,
	    &priv->pkstats.rx_length_errors, 0, "RX Length Errors");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_over_errors", CTLFLAG_RD,
	    &priv->pkstats.rx_over_errors, 0, "RX Over Errors");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_crc_errors", CTLFLAG_RD,
	    &priv->pkstats.rx_crc_errors, 0, "RX CRC Errors");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_jabbers", CTLFLAG_RD,
	    &priv->pkstats.rx_jabbers, 0, "RX Jabbers");

	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_in_range_length_error", CTLFLAG_RD,
	    &priv->pkstats.rx_in_range_length_error, 0, "RX IN_Range Length Error");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_out_range_length_error",
	    CTLFLAG_RD, &priv->pkstats.rx_out_range_length_error, 0,
	    "RX Out Range Length Error");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_lt_64_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_lt_64_bytes_packets, 0, "RX Lt 64 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_127_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_127_bytes_packets, 0, "RX 127 bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_255_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_255_bytes_packets, 0, "RX 255 bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_511_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_511_bytes_packets, 0, "RX 511 bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_1023_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_1023_bytes_packets, 0, "RX 1023 bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_1518_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_1518_bytes_packets, 0, "RX 1518 bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_1522_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_1522_bytes_packets, 0, "RX 1522 bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_1548_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_1548_bytes_packets, 0, "RX 1548 bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "rx_gt_1548_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.rx_gt_1548_bytes_packets, 0,
	    "RX Greater Then 1548 bytes Packets");

	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_packets, 0, "TX packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_bytes", CTLFLAG_RD,
	    &priv->pkstats.tx_bytes, 0, "TX Bytes");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_multicast_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_multicast_packets, 0, "TX Multicast Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_broadcast_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_broadcast_packets, 0, "TX Broadcast Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_errors", CTLFLAG_RD,
	    &priv->pkstats.tx_errors, 0, "TX Errors");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_dropped", CTLFLAG_RD,
	    &priv->pkstats.tx_dropped, 0, "TX Dropped");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_lt_64_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_lt_64_bytes_packets, 0, "TX Less Then 64 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_127_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_127_bytes_packets, 0, "TX 127 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_255_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_255_bytes_packets, 0, "TX 255 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_511_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_511_bytes_packets, 0, "TX 511 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_1023_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_1023_bytes_packets, 0, "TX 1023 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_1518_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_1518_bytes_packets, 0, "TX 1518 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_1522_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_1522_bytes_packets, 0, "TX 1522 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_1548_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_1548_bytes_packets, 0, "TX 1548 Bytes Packets");
	SYSCTL_ADD_U64(ctx, node_list, OID_AUTO, "tx_gt_1548_bytes_packets", CTLFLAG_RD,
	    &priv->pkstats.tx_gt_1548_bytes_packets, 0,
	    "TX Greater Then 1548 Bytes Packets");

	for (i = 0; i < priv->tx_ring_num; i++) {
		tx_ring = priv->tx_ring[i];
		snprintf(namebuf, sizeof(namebuf), "tx_ring%d", i);
		ring_node = SYSCTL_ADD_NODE(ctx, node_list, OID_AUTO, namebuf,
		    CTLFLAG_RD, NULL, "TX Ring");
		ring_list = SYSCTL_CHILDREN(ring_node);
		SYSCTL_ADD_U64(ctx, ring_list, OID_AUTO, "packets",
		    CTLFLAG_RD, &tx_ring->packets, 0, "TX packets");
		SYSCTL_ADD_U64(ctx, ring_list, OID_AUTO, "bytes",
		    CTLFLAG_RD, &tx_ring->bytes, 0, "TX bytes");
		SYSCTL_ADD_U64(ctx, ring_list, OID_AUTO, "tso_packets",
		    CTLFLAG_RD, &tx_ring->tso_packets, 0, "TSO packets");
		SYSCTL_ADD_U64(ctx, ring_list, OID_AUTO, "defrag_attempts",
		    CTLFLAG_RD, &tx_ring->defrag_attempts, 0,
		    "Oversized chains defragged");
	}

	for (i = 0; i < priv->rx_ring_num; i++) {
		rx_ring = priv->rx_ring[i];
		snprintf(namebuf, sizeof(namebuf), "rx_ring%d", i);
		ring_node = SYSCTL_ADD_NODE(ctx, node_list, OID_AUTO, namebuf,
		    CTLFLAG_RD, NULL, "RX Ring");
		ring_list = SYSCTL_CHILDREN(ring_node);
		SYSCTL_ADD_U64(ctx, ring_list, OID_AUTO, "packets",
		    CTLFLAG_RD, &rx_ring->packets, 0, "RX packets");
		SYSCTL_ADD_U64(ctx, ring_list, OID_AUTO, "bytes",
		    CTLFLAG_RD, &rx_ring->bytes, 0, "RX bytes");
		SYSCTL_ADD_U64(ctx, ring_list, OID_AUTO, "error",
		    CTLFLAG_RD, &rx_ring->errors, 0, "RX soft errors");
	}
}