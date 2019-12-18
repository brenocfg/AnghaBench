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
struct nfe_hw_stats {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_deferals; int /*<<< orphan*/  tx_retry_errors; int /*<<< orphan*/  tx_excess_deferals; int /*<<< orphan*/  tx_carrier_losts; int /*<<< orphan*/  tx_fifo_underuns; int /*<<< orphan*/  tx_late_cols; int /*<<< orphan*/  tx_multi_rexmits; int /*<<< orphan*/  tx_one_rexmits; int /*<<< orphan*/  tx_zero_rexmits; int /*<<< orphan*/  tx_octets; int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  rx_octets; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  rx_fae; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_overuns; int /*<<< orphan*/  rx_jumbos; int /*<<< orphan*/  rx_runts; int /*<<< orphan*/  rx_late_cols; int /*<<< orphan*/  rx_extra_bytes; int /*<<< orphan*/  rx_frame_errors; } ;
struct nfe_softc {scalar_t__ nfe_process_limit; int nfe_flags; int /*<<< orphan*/  nfe_dev; struct nfe_hw_stats nfe_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int NFE_MIB_V1 ; 
 int NFE_MIB_V2 ; 
 int NFE_MIB_V3 ; 
 void* NFE_PROC_DEFAULT ; 
 scalar_t__ NFE_PROC_MAX ; 
 scalar_t__ NFE_PROC_MIN ; 
 int /*<<< orphan*/  NFE_SYSCTL_STAT_ADD32 (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NFE_SYSCTL_STAT_ADD64 (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
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
 int /*<<< orphan*/  sysctl_hw_nfe_proc_limit ; 

__attribute__((used)) static void
nfe_sysctl_node(struct nfe_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child, *parent;
	struct sysctl_oid *tree;
	struct nfe_hw_stats *stats;
	int error;

	stats = &sc->nfe_stats;
	ctx = device_get_sysctl_ctx(sc->nfe_dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->nfe_dev));
	SYSCTL_ADD_PROC(ctx, child,
	    OID_AUTO, "process_limit", CTLTYPE_INT | CTLFLAG_RW,
	    &sc->nfe_process_limit, 0, sysctl_hw_nfe_proc_limit, "I",
	    "max number of Rx events to process");

	sc->nfe_process_limit = NFE_PROC_DEFAULT;
	error = resource_int_value(device_get_name(sc->nfe_dev),
	    device_get_unit(sc->nfe_dev), "process_limit",
	    &sc->nfe_process_limit);
	if (error == 0) {
		if (sc->nfe_process_limit < NFE_PROC_MIN ||
		    sc->nfe_process_limit > NFE_PROC_MAX) {
			device_printf(sc->nfe_dev,
			    "process_limit value out of range; "
			    "using default: %d\n", NFE_PROC_DEFAULT);
			sc->nfe_process_limit = NFE_PROC_DEFAULT;
		}
	}

	if ((sc->nfe_flags & (NFE_MIB_V1 | NFE_MIB_V2 | NFE_MIB_V3)) == 0)
		return;

	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "NFE statistics");
	parent = SYSCTL_CHILDREN(tree);

	/* Rx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "rx", CTLFLAG_RD,
	    NULL, "Rx MAC statistics");
	child = SYSCTL_CHILDREN(tree);

	NFE_SYSCTL_STAT_ADD32(ctx, child, "frame_errors",
	    &stats->rx_frame_errors, "Framing Errors");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "extra_bytes",
	    &stats->rx_extra_bytes, "Extra Bytes");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "late_cols",
	    &stats->rx_late_cols, "Late Collisions");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "runts",
	    &stats->rx_runts, "Runts");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "jumbos",
	    &stats->rx_jumbos, "Jumbos");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "fifo_overuns",
	    &stats->rx_fifo_overuns, "FIFO Overruns");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "crc_errors",
	    &stats->rx_crc_errors, "CRC Errors");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "fae",
	    &stats->rx_fae, "Frame Alignment Errors");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "len_errors",
	    &stats->rx_len_errors, "Length Errors");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "unicast",
	    &stats->rx_unicast, "Unicast Frames");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "multicast",
	    &stats->rx_multicast, "Multicast Frames");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "broadcast",
	    &stats->rx_broadcast, "Broadcast Frames");
	if ((sc->nfe_flags & NFE_MIB_V2) != 0) {
		NFE_SYSCTL_STAT_ADD64(ctx, child, "octets",
		    &stats->rx_octets, "Octets");
		NFE_SYSCTL_STAT_ADD32(ctx, child, "pause",
		    &stats->rx_pause, "Pause frames");
		NFE_SYSCTL_STAT_ADD32(ctx, child, "drops",
		    &stats->rx_drops, "Drop frames");
	}

	/* Tx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "tx", CTLFLAG_RD,
	    NULL, "Tx MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	NFE_SYSCTL_STAT_ADD64(ctx, child, "octets",
	    &stats->tx_octets, "Octets");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "zero_rexmits",
	    &stats->tx_zero_rexmits, "Zero Retransmits");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "one_rexmits",
	    &stats->tx_one_rexmits, "One Retransmits");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "multi_rexmits",
	    &stats->tx_multi_rexmits, "Multiple Retransmits");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "late_cols",
	    &stats->tx_late_cols, "Late Collisions");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "fifo_underuns",
	    &stats->tx_fifo_underuns, "FIFO Underruns");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "carrier_losts",
	    &stats->tx_carrier_losts, "Carrier Losts");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "excess_deferrals",
	    &stats->tx_excess_deferals, "Excess Deferrals");
	NFE_SYSCTL_STAT_ADD32(ctx, child, "retry_errors",
	    &stats->tx_retry_errors, "Retry Errors");
	if ((sc->nfe_flags & NFE_MIB_V2) != 0) {
		NFE_SYSCTL_STAT_ADD32(ctx, child, "deferrals",
		    &stats->tx_deferals, "Deferrals");
		NFE_SYSCTL_STAT_ADD32(ctx, child, "frames",
		    &stats->tx_frames, "Frames");
		NFE_SYSCTL_STAT_ADD32(ctx, child, "pause",
		    &stats->tx_pause, "Pause Frames");
	}
	if ((sc->nfe_flags & NFE_MIB_V3) != 0) {
		NFE_SYSCTL_STAT_ADD32(ctx, child, "unicast",
		    &stats->tx_deferals, "Unicast Frames");
		NFE_SYSCTL_STAT_ADD32(ctx, child, "multicast",
		    &stats->tx_frames, "Multicast Frames");
		NFE_SYSCTL_STAT_ADD32(ctx, child, "broadcast",
		    &stats->tx_pause, "Broadcast Frames");
	}
}