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
struct nge_stats {int /*<<< orphan*/  tx_seq_errs; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  rx_unctl_frames; int /*<<< orphan*/  rx_len_errs; int /*<<< orphan*/  rx_pkts_jumbos; int /*<<< orphan*/  rx_sym_errs; int /*<<< orphan*/  rx_align_errs; int /*<<< orphan*/  rx_fifo_oflows; int /*<<< orphan*/  rx_crc_errs; int /*<<< orphan*/  rx_pkts_errs; } ;
struct nge_softc {int nge_int_holdoff; struct nge_stats nge_stats; int /*<<< orphan*/  nge_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int NGE_INT_HOLDOFF_DEFAULT ; 
 int NGE_INT_HOLDOFF_MAX ; 
 int NGE_INT_HOLDOFF_MIN ; 
 int /*<<< orphan*/  NGE_SYSCTL_STAT_ADD32 (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  sysctl_hw_nge_int_holdoff ; 

__attribute__((used)) static void
nge_sysctl_node(struct nge_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child, *parent;
	struct sysctl_oid *tree;
	struct nge_stats *stats;
	int error;

	ctx = device_get_sysctl_ctx(sc->nge_dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->nge_dev));
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "int_holdoff",
	    CTLTYPE_INT | CTLFLAG_RW, &sc->nge_int_holdoff, 0,
	    sysctl_hw_nge_int_holdoff, "I", "NGE interrupt moderation");
	/* Pull in device tunables. */
	sc->nge_int_holdoff = NGE_INT_HOLDOFF_DEFAULT;
	error = resource_int_value(device_get_name(sc->nge_dev),
	    device_get_unit(sc->nge_dev), "int_holdoff", &sc->nge_int_holdoff);
	if (error == 0) {
		if (sc->nge_int_holdoff < NGE_INT_HOLDOFF_MIN ||
		    sc->nge_int_holdoff > NGE_INT_HOLDOFF_MAX ) {
			device_printf(sc->nge_dev,
			    "int_holdoff value out of range; "
			    "using default: %d(%d us)\n",
			    NGE_INT_HOLDOFF_DEFAULT,
			    NGE_INT_HOLDOFF_DEFAULT * 100);
			sc->nge_int_holdoff = NGE_INT_HOLDOFF_DEFAULT;
		}
	}

	stats = &sc->nge_stats;
	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "NGE statistics");
	parent = SYSCTL_CHILDREN(tree);

	/* Rx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "rx", CTLFLAG_RD,
	    NULL, "Rx MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	NGE_SYSCTL_STAT_ADD32(ctx, child, "pkts_errs",
	    &stats->rx_pkts_errs,
	    "Packet errors including both wire errors and FIFO overruns");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "crc_errs",
	    &stats->rx_crc_errs, "CRC errors");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "fifo_oflows",
	    &stats->rx_fifo_oflows, "FIFO overflows");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "align_errs",
	    &stats->rx_align_errs, "Frame alignment errors");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "sym_errs",
	    &stats->rx_sym_errs, "One or more symbol errors");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "pkts_jumbos",
	    &stats->rx_pkts_jumbos,
	    "Packets received with length greater than 1518 bytes");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "len_errs",
	    &stats->rx_len_errs, "In Range Length errors");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "unctl_frames",
	    &stats->rx_unctl_frames, "Control frames with unsupported opcode");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "pause",
	    &stats->rx_pause, "Pause frames");

	/* Tx statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "tx", CTLFLAG_RD,
	    NULL, "Tx MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	NGE_SYSCTL_STAT_ADD32(ctx, child, "pause",
	    &stats->tx_pause, "Pause frames");
	NGE_SYSCTL_STAT_ADD32(ctx, child, "seq_errs",
	    &stats->tx_seq_errs,
	    "Loss of collision heartbeat during transmission");
}