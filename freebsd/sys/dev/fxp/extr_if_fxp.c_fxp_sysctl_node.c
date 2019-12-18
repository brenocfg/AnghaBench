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
struct fxp_hwstats {int /*<<< orphan*/  tx_tco; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_total_collisions; int /*<<< orphan*/  tx_multiple_collisions; int /*<<< orphan*/  tx_single_collisions; int /*<<< orphan*/  tx_deffered; int /*<<< orphan*/  tx_lostcrs; int /*<<< orphan*/  tx_underruns; int /*<<< orphan*/  tx_latecols; int /*<<< orphan*/  tx_maxcols; int /*<<< orphan*/  tx_good; int /*<<< orphan*/  rx_tco; int /*<<< orphan*/  rx_controls; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  rx_shortframes; int /*<<< orphan*/  rx_cdt_errors; int /*<<< orphan*/  rx_overrun_errors; int /*<<< orphan*/  rx_rnr_errors; int /*<<< orphan*/  rx_alignment_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_good; } ;
struct fxp_softc {scalar_t__ revision; struct fxp_hwstats fxp_hwstats; scalar_t__ rnr; int /*<<< orphan*/  tunable_bundle_max; int /*<<< orphan*/  dev; int /*<<< orphan*/  tunable_int_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 scalar_t__ FXP_REV_82558_A4 ; 
 scalar_t__ FXP_REV_82559_A0 ; 
 int /*<<< orphan*/  FXP_SYSCTL_STAT_ADD (struct sysctl_ctx_list*,struct sysctl_oid_list*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  TUNABLE_BUNDLE_MAX ; 
 int /*<<< orphan*/  TUNABLE_INT_DELAY ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_hw_fxp_bundle_max ; 
 int /*<<< orphan*/  sysctl_hw_fxp_int_delay ; 

__attribute__((used)) static void
fxp_sysctl_node(struct fxp_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child, *parent;
	struct sysctl_oid *tree;
	struct fxp_hwstats *hsp;

	ctx = device_get_sysctl_ctx(sc->dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev));

	SYSCTL_ADD_PROC(ctx, child,
	    OID_AUTO, "int_delay", CTLTYPE_INT | CTLFLAG_RW,
	    &sc->tunable_int_delay, 0, sysctl_hw_fxp_int_delay, "I",
	    "FXP driver receive interrupt microcode bundling delay");
	SYSCTL_ADD_PROC(ctx, child,
	    OID_AUTO, "bundle_max", CTLTYPE_INT | CTLFLAG_RW,
	    &sc->tunable_bundle_max, 0, sysctl_hw_fxp_bundle_max, "I",
	    "FXP driver receive interrupt microcode bundle size limit");
	SYSCTL_ADD_INT(ctx, child,OID_AUTO, "rnr", CTLFLAG_RD, &sc->rnr, 0,
	    "FXP RNR events");

	/*
	 * Pull in device tunables.
	 */
	sc->tunable_int_delay = TUNABLE_INT_DELAY;
	sc->tunable_bundle_max = TUNABLE_BUNDLE_MAX;
	(void) resource_int_value(device_get_name(sc->dev),
	    device_get_unit(sc->dev), "int_delay", &sc->tunable_int_delay);
	(void) resource_int_value(device_get_name(sc->dev),
	    device_get_unit(sc->dev), "bundle_max", &sc->tunable_bundle_max);
	sc->rnr = 0;

	hsp = &sc->fxp_hwstats;
	tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "FXP statistics");
	parent = SYSCTL_CHILDREN(tree);

	/* Rx MAC statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "rx", CTLFLAG_RD,
	    NULL, "Rx MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	FXP_SYSCTL_STAT_ADD(ctx, child, "good_frames",
	    &hsp->rx_good, "Good frames");
	FXP_SYSCTL_STAT_ADD(ctx, child, "crc_errors",
	    &hsp->rx_crc_errors, "CRC errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "alignment_errors",
	    &hsp->rx_alignment_errors, "Alignment errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "rnr_errors",
	    &hsp->rx_rnr_errors, "RNR errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "overrun_errors",
	    &hsp->rx_overrun_errors, "Overrun errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "cdt_errors",
	    &hsp->rx_cdt_errors, "Collision detect errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "shortframes",
	    &hsp->rx_shortframes, "Short frame errors");
	if (sc->revision >= FXP_REV_82558_A4) {
		FXP_SYSCTL_STAT_ADD(ctx, child, "pause",
		    &hsp->rx_pause, "Pause frames");
		FXP_SYSCTL_STAT_ADD(ctx, child, "controls",
		    &hsp->rx_controls, "Unsupported control frames");
	}
	if (sc->revision >= FXP_REV_82559_A0)
		FXP_SYSCTL_STAT_ADD(ctx, child, "tco",
		    &hsp->rx_tco, "TCO frames");

	/* Tx MAC statistics. */
	tree = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO, "tx", CTLFLAG_RD,
	    NULL, "Tx MAC statistics");
	child = SYSCTL_CHILDREN(tree);
	FXP_SYSCTL_STAT_ADD(ctx, child, "good_frames",
	    &hsp->tx_good, "Good frames");
	FXP_SYSCTL_STAT_ADD(ctx, child, "maxcols",
	    &hsp->tx_maxcols, "Maximum collisions errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "latecols",
	    &hsp->tx_latecols, "Late collisions errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "underruns",
	    &hsp->tx_underruns, "Underrun errors");
	FXP_SYSCTL_STAT_ADD(ctx, child, "lostcrs",
	    &hsp->tx_lostcrs, "Lost carrier sense");
	FXP_SYSCTL_STAT_ADD(ctx, child, "deffered",
	    &hsp->tx_deffered, "Deferred");
	FXP_SYSCTL_STAT_ADD(ctx, child, "single_collisions",
	    &hsp->tx_single_collisions, "Single collisions");
	FXP_SYSCTL_STAT_ADD(ctx, child, "multiple_collisions",
	    &hsp->tx_multiple_collisions, "Multiple collisions");
	FXP_SYSCTL_STAT_ADD(ctx, child, "total_collisions",
	    &hsp->tx_total_collisions, "Total collisions");
	if (sc->revision >= FXP_REV_82558_A4)
		FXP_SYSCTL_STAT_ADD(ctx, child, "pause",
		    &hsp->tx_pause, "Pause frames");
	if (sc->revision >= FXP_REV_82559_A0)
		FXP_SYSCTL_STAT_ADD(ctx, child, "tco",
		    &hsp->tx_tco, "TCO frames");
}