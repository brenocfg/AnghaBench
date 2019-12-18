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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct ale_hw_stats {int /*<<< orphan*/  tx_pkts_truncated; int /*<<< orphan*/  tx_lenerrs; int /*<<< orphan*/  tx_desc_underrun; int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  tx_excess_colls; int /*<<< orphan*/  tx_late_colls; int /*<<< orphan*/  tx_multi_colls; int /*<<< orphan*/  tx_single_colls; int /*<<< orphan*/  tx_pkts_1519_max; int /*<<< orphan*/  tx_pkts_1024_1518; int /*<<< orphan*/  tx_pkts_512_1023; int /*<<< orphan*/  tx_pkts_256_511; int /*<<< orphan*/  tx_pkts_128_255; int /*<<< orphan*/  tx_pkts_65_127; int /*<<< orphan*/  tx_pkts_64; int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_bcast_bytes; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_excess_defer; int /*<<< orphan*/  tx_control_frames; int /*<<< orphan*/  tx_pause_frames; int /*<<< orphan*/  tx_mcast_frames; int /*<<< orphan*/  tx_bcast_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_pkts_filtered; int /*<<< orphan*/  rx_alignerrs; int /*<<< orphan*/  rx_rrs_errs; int /*<<< orphan*/  rx_fifo_oflows; int /*<<< orphan*/  rx_pkts_truncated; int /*<<< orphan*/  rx_pkts_1519_max; int /*<<< orphan*/  rx_pkts_1024_1518; int /*<<< orphan*/  rx_pkts_512_1023; int /*<<< orphan*/  rx_pkts_256_511; int /*<<< orphan*/  rx_pkts_128_255; int /*<<< orphan*/  rx_pkts_65_127; int /*<<< orphan*/  rx_pkts_64; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_runts; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_lenerrs; int /*<<< orphan*/  rx_crcerrs; int /*<<< orphan*/  rx_control_frames; int /*<<< orphan*/  rx_pause_frames; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_bcast_frames; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  reset_brk_seq; } ;
struct ale_softc {scalar_t__ ale_int_rx_mod; scalar_t__ ale_int_tx_mod; scalar_t__ ale_process_limit; int /*<<< orphan*/  ale_dev; struct ale_hw_stats ale_stats; } ;

/* Variables and functions */
 void* ALE_IM_RX_TIMER_DEFAULT ; 
 scalar_t__ ALE_IM_TIMER_MAX ; 
 scalar_t__ ALE_IM_TIMER_MIN ; 
 void* ALE_IM_TX_TIMER_DEFAULT ; 
 void* ALE_PROC_DEFAULT ; 
 scalar_t__ ALE_PROC_MAX ; 
 scalar_t__ ALE_PROC_MIN ; 
 int /*<<< orphan*/  ALE_SYSCTL_STAT_ADD32 (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ALE_SYSCTL_STAT_ADD64 (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,void*) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  sysctl_hw_ale_int_mod ; 
 int /*<<< orphan*/  sysctl_hw_ale_proc_limit ; 

__attribute__((used)) static void
ale_sysctl_node(struct ale_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child, *parent;
	struct sysctl_oid *tree;
	struct ale_hw_stats *stats;
	int error;

	stats = &sc->ale_stats;
	ctx = device_get_sysctl_ctx(sc->ale_dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->ale_dev));

	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "int_rx_mod",
	    CTLTYPE_INT | CTLFLAG_RW, &sc->ale_int_rx_mod, 0,
	    sysctl_hw_ale_int_mod, "I", "ale Rx interrupt moderation");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "int_tx_mod",
	    CTLTYPE_INT | CTLFLAG_RW, &sc->ale_int_tx_mod, 0,
	    sysctl_hw_ale_int_mod, "I", "ale Tx interrupt moderation");
	/* Pull in device tunables. */
	sc->ale_int_rx_mod = ALE_IM_RX_TIMER_DEFAULT;
	error = resource_int_value(device_get_name(sc->ale_dev),
	    device_get_unit(sc->ale_dev), "int_rx_mod", &sc->ale_int_rx_mod);
	if (error == 0) {
		if (sc->ale_int_rx_mod < ALE_IM_TIMER_MIN ||
		    sc->ale_int_rx_mod > ALE_IM_TIMER_MAX) {
			device_printf(sc->ale_dev, "int_rx_mod value out of "
			    "range; using default: %d\n",
			    ALE_IM_RX_TIMER_DEFAULT);
			sc->ale_int_rx_mod = ALE_IM_RX_TIMER_DEFAULT;
		}
	}
	sc->ale_int_tx_mod = ALE_IM_TX_TIMER_DEFAULT;
	error = resource_int_value(device_get_name(sc->ale_dev),
	    device_get_unit(sc->ale_dev), "int_tx_mod", &sc->ale_int_tx_mod);
	if (error == 0) {
		if (sc->ale_int_tx_mod < ALE_IM_TIMER_MIN ||
		    sc->ale_int_tx_mod > ALE_IM_TIMER_MAX) {
			device_printf(sc->ale_dev, "int_tx_mod value out of "
			    "range; using default: %d\n",
			    ALE_IM_TX_TIMER_DEFAULT);
			sc->ale_int_tx_mod = ALE_IM_TX_TIMER_DEFAULT;
		}
	}
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "process_limit",
	    CTLTYPE_INT | CTLFLAG_RW, &sc->ale_process_limit, 0,
	    sysctl_hw_ale_proc_limit, "I",
	    "max number of Rx events to process");
	/* Pull in device tunables. */
	sc->ale_process_limit = ALE_PROC_DEFAULT;
	error = resource_int_value(device_get_name(sc->ale_dev),
	    device_get_unit(sc->ale_dev), "process_limit",
	    &sc->ale_process_limit);
	if (error == 0) {
		if (sc->ale_process_limit < ALE_PROC_MIN ||
		    sc->ale_process_limit > ALE_PROC_MAX) {
			device_printf(sc->ale_dev,
			    "process_limit value out of range; "
			    "using default: %d\n", ALE_PROC_DEFAULT);
			sc->ale_process_limit = ALE_PROC_DEFAULT;
		}
	}

	/* Misc statistics. */
	ALE_SYSCTL_STAT_ADD32(ctx, child, "reset_brk_seq",
	    &stats->reset_brk_seq,
	    "Controller resets due to broken Rx sequnce number");

	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "ATE statistics");
	parent = SYSCTL_CHILDREN(tree);

	/* Rx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "rx", CTLFLAG_RD,
	    NULL, "Rx MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	ALE_SYSCTL_STAT_ADD32(ctx, child, "good_frames",
	    &stats->rx_frames, "Good frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "good_bcast_frames",
	    &stats->rx_bcast_frames, "Good broadcast frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "good_mcast_frames",
	    &stats->rx_mcast_frames, "Good multicast frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "pause_frames",
	    &stats->rx_pause_frames, "Pause control frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "control_frames",
	    &stats->rx_control_frames, "Control frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "crc_errs",
	    &stats->rx_crcerrs, "CRC errors");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "len_errs",
	    &stats->rx_lenerrs, "Frames with length mismatched");
	ALE_SYSCTL_STAT_ADD64(ctx, child, "good_octets",
	    &stats->rx_bytes, "Good octets");
	ALE_SYSCTL_STAT_ADD64(ctx, child, "good_bcast_octets",
	    &stats->rx_bcast_bytes, "Good broadcast octets");
	ALE_SYSCTL_STAT_ADD64(ctx, child, "good_mcast_octets",
	    &stats->rx_mcast_bytes, "Good multicast octets");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "runts",
	    &stats->rx_runts, "Too short frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "fragments",
	    &stats->rx_fragments, "Fragmented frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_64",
	    &stats->rx_pkts_64, "64 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_65_127",
	    &stats->rx_pkts_65_127, "65 to 127 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_128_255",
	    &stats->rx_pkts_128_255, "128 to 255 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_256_511",
	    &stats->rx_pkts_256_511, "256 to 511 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_512_1023",
	    &stats->rx_pkts_512_1023, "512 to 1023 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_1024_1518",
	    &stats->rx_pkts_1024_1518, "1024 to 1518 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_1519_max",
	    &stats->rx_pkts_1519_max, "1519 to max frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "trunc_errs",
	    &stats->rx_pkts_truncated, "Truncated frames due to MTU size");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "fifo_oflows",
	    &stats->rx_fifo_oflows, "FIFO overflows");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "rrs_errs",
	    &stats->rx_rrs_errs, "Return status write-back errors");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "align_errs",
	    &stats->rx_alignerrs, "Alignment errors");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "filtered",
	    &stats->rx_pkts_filtered,
	    "Frames dropped due to address filtering");

	/* Tx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "tx", CTLFLAG_RD,
	    NULL, "Tx MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	ALE_SYSCTL_STAT_ADD32(ctx, child, "good_frames",
	    &stats->tx_frames, "Good frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "good_bcast_frames",
	    &stats->tx_bcast_frames, "Good broadcast frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "good_mcast_frames",
	    &stats->tx_mcast_frames, "Good multicast frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "pause_frames",
	    &stats->tx_pause_frames, "Pause control frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "control_frames",
	    &stats->tx_control_frames, "Control frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "excess_defers",
	    &stats->tx_excess_defer, "Frames with excessive derferrals");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "defers",
	    &stats->tx_excess_defer, "Frames with derferrals");
	ALE_SYSCTL_STAT_ADD64(ctx, child, "good_octets",
	    &stats->tx_bytes, "Good octets");
	ALE_SYSCTL_STAT_ADD64(ctx, child, "good_bcast_octets",
	    &stats->tx_bcast_bytes, "Good broadcast octets");
	ALE_SYSCTL_STAT_ADD64(ctx, child, "good_mcast_octets",
	    &stats->tx_mcast_bytes, "Good multicast octets");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_64",
	    &stats->tx_pkts_64, "64 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_65_127",
	    &stats->tx_pkts_65_127, "65 to 127 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_128_255",
	    &stats->tx_pkts_128_255, "128 to 255 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_256_511",
	    &stats->tx_pkts_256_511, "256 to 511 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_512_1023",
	    &stats->tx_pkts_512_1023, "512 to 1023 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_1024_1518",
	    &stats->tx_pkts_1024_1518, "1024 to 1518 bytes frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "frames_1519_max",
	    &stats->tx_pkts_1519_max, "1519 to max frames");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "single_colls",
	    &stats->tx_single_colls, "Single collisions");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "multi_colls",
	    &stats->tx_multi_colls, "Multiple collisions");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "late_colls",
	    &stats->tx_late_colls, "Late collisions");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "excess_colls",
	    &stats->tx_excess_colls, "Excessive collisions");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "underruns",
	    &stats->tx_underrun, "FIFO underruns");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "desc_underruns",
	    &stats->tx_desc_underrun, "Descriptor write-back errors");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "len_errs",
	    &stats->tx_lenerrs, "Frames with length mismatched");
	ALE_SYSCTL_STAT_ADD32(ctx, child, "trunc_errs",
	    &stats->tx_pkts_truncated, "Truncated frames due to MTU size");
}