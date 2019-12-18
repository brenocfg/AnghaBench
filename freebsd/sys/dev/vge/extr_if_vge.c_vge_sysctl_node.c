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
struct vge_hw_stats {int /*<<< orphan*/  tx_sqeerrs; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_latecolls; int /*<<< orphan*/  tx_colls; int /*<<< orphan*/  tx_jumbos; int /*<<< orphan*/  tx_pkts_1024_1518; int /*<<< orphan*/  tx_pkts_512_1023; int /*<<< orphan*/  tx_pkts_256_511; int /*<<< orphan*/  tx_pkts_128_255; int /*<<< orphan*/  tx_pkts_65_127; int /*<<< orphan*/  tx_pkts_64; int /*<<< orphan*/  tx_good_frames; int /*<<< orphan*/  rx_lenerrs; int /*<<< orphan*/  rx_symerrs; int /*<<< orphan*/  rx_nobufs; int /*<<< orphan*/  rx_alignerrs; int /*<<< orphan*/  rx_pause_frames; int /*<<< orphan*/  rx_crcerrs; int /*<<< orphan*/  rx_jumbos; int /*<<< orphan*/  rx_pkts_1519_max_errs; int /*<<< orphan*/  rx_pkts_1519_max; int /*<<< orphan*/  rx_pkts_1024_1518; int /*<<< orphan*/  rx_pkts_512_1023; int /*<<< orphan*/  rx_pkts_256_511; int /*<<< orphan*/  rx_pkts_128_255; int /*<<< orphan*/  rx_pkts_65_127; int /*<<< orphan*/  rx_pkts_64; int /*<<< orphan*/  rx_runts_errs; int /*<<< orphan*/  rx_runts; int /*<<< orphan*/  rx_fifo_oflows; int /*<<< orphan*/  rx_good_frames; int /*<<< orphan*/  rx_frames; } ;
struct vge_softc {int /*<<< orphan*/  vge_tx_coal_pkt; int /*<<< orphan*/  vge_dev; int /*<<< orphan*/  vge_rx_coal_pkt; int /*<<< orphan*/  vge_int_holdoff; struct vge_hw_stats vge_stats; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  VGE_INT_HOLDOFF_DEFAULT ; 
 int /*<<< orphan*/  VGE_RX_COAL_PKT_DEFAULT ; 
 int /*<<< orphan*/  VGE_SYSCTL_STAT_ADD32 (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VGE_TX_COAL_PKT_DEFAULT ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vge_stats_clear (struct vge_softc*) ; 

__attribute__((used)) static void
vge_sysctl_node(struct vge_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child, *parent;
	struct sysctl_oid *tree;
	struct vge_hw_stats *stats;

	stats = &sc->vge_stats;
	ctx = device_get_sysctl_ctx(sc->vge_dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->vge_dev));

	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "int_holdoff",
	    CTLFLAG_RW, &sc->vge_int_holdoff, 0, "interrupt holdoff");
	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "rx_coal_pkt",
	    CTLFLAG_RW, &sc->vge_rx_coal_pkt, 0, "rx coalescing packet");
	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "tx_coal_pkt",
	    CTLFLAG_RW, &sc->vge_tx_coal_pkt, 0, "tx coalescing packet");

	/* Pull in device tunables. */
	sc->vge_int_holdoff = VGE_INT_HOLDOFF_DEFAULT;
	resource_int_value(device_get_name(sc->vge_dev),
	    device_get_unit(sc->vge_dev), "int_holdoff", &sc->vge_int_holdoff);
	sc->vge_rx_coal_pkt = VGE_RX_COAL_PKT_DEFAULT;
	resource_int_value(device_get_name(sc->vge_dev),
	    device_get_unit(sc->vge_dev), "rx_coal_pkt", &sc->vge_rx_coal_pkt);
	sc->vge_tx_coal_pkt = VGE_TX_COAL_PKT_DEFAULT;
	resource_int_value(device_get_name(sc->vge_dev),
	    device_get_unit(sc->vge_dev), "tx_coal_pkt", &sc->vge_tx_coal_pkt);

	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "VGE statistics");
	parent = SYSCTL_CHILDREN(tree);

	/* Rx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "rx", CTLFLAG_RD,
	    NULL, "RX MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames",
	    &stats->rx_frames, "frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "good_frames",
	    &stats->rx_good_frames, "Good frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "fifo_oflows",
	    &stats->rx_fifo_oflows, "FIFO overflows");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "runts",
	    &stats->rx_runts, "Too short frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "runts_errs",
	    &stats->rx_runts_errs, "Too short frames with errors");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_64",
	    &stats->rx_pkts_64, "64 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_65_127",
	    &stats->rx_pkts_65_127, "65 to 127 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_128_255",
	    &stats->rx_pkts_128_255, "128 to 255 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_256_511",
	    &stats->rx_pkts_256_511, "256 to 511 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_512_1023",
	    &stats->rx_pkts_512_1023, "512 to 1023 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_1024_1518",
	    &stats->rx_pkts_1024_1518, "1024 to 1518 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_1519_max",
	    &stats->rx_pkts_1519_max, "1519 to max frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_1519_max_errs",
	    &stats->rx_pkts_1519_max_errs, "1519 to max frames with error");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_jumbo",
	    &stats->rx_jumbos, "Jumbo frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "crcerrs",
	    &stats->rx_crcerrs, "CRC errors");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "pause_frames",
	    &stats->rx_pause_frames, "CRC errors");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "align_errs",
	    &stats->rx_alignerrs, "Alignment errors");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "nobufs",
	    &stats->rx_nobufs, "Frames with no buffer event");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "sym_errs",
	    &stats->rx_symerrs, "Frames with symbol errors");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "len_errs",
	    &stats->rx_lenerrs, "Frames with length mismatched");

	/* Tx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "tx", CTLFLAG_RD,
	    NULL, "TX MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	VGE_SYSCTL_STAT_ADD32(ctx, child, "good_frames",
	    &stats->tx_good_frames, "Good frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_64",
	    &stats->tx_pkts_64, "64 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_65_127",
	    &stats->tx_pkts_65_127, "65 to 127 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_128_255",
	    &stats->tx_pkts_128_255, "128 to 255 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_256_511",
	    &stats->tx_pkts_256_511, "256 to 511 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_512_1023",
	    &stats->tx_pkts_512_1023, "512 to 1023 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_1024_1518",
	    &stats->tx_pkts_1024_1518, "1024 to 1518 bytes frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "frames_jumbo",
	    &stats->tx_jumbos, "Jumbo frames");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "colls",
	    &stats->tx_colls, "Collisions");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "late_colls",
	    &stats->tx_latecolls, "Late collisions");
	VGE_SYSCTL_STAT_ADD32(ctx, child, "pause_frames",
	    &stats->tx_pause, "Pause frames");
#ifdef VGE_ENABLE_SQEERR
	VGE_SYSCTL_STAT_ADD32(ctx, child, "sqeerrs",
	    &stats->tx_sqeerrs, "SQE errors");
#endif
	/* Clear MAC statistics. */
	vge_stats_clear(sc);
}