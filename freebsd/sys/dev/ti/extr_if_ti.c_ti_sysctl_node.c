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
typedef  int /*<<< orphan*/  tname ;
struct ti_softc {int ti_dac; int ti_rx_coal_ticks; int ti_rx_max_coal_bds; int ti_tx_coal_ticks; int ti_tx_max_coal_bds; int ti_tx_buf_ratio; int ti_stat_ticks; int /*<<< orphan*/  ti_dev; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int TI_TICKS_PER_SEC ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int,char*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
ti_sysctl_node(struct ti_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *child;
	char tname[32];

	ctx = device_get_sysctl_ctx(sc->ti_dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->ti_dev));

	/* Use DAC */
	sc->ti_dac = 1;
	snprintf(tname, sizeof(tname), "dev.ti.%d.dac",
	    device_get_unit(sc->ti_dev));
	TUNABLE_INT_FETCH(tname, &sc->ti_dac);

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_coal_ticks", CTLFLAG_RW,
	    &sc->ti_rx_coal_ticks, 0, "Receive coalcesced ticks");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rx_max_coal_bds", CTLFLAG_RW,
	    &sc->ti_rx_max_coal_bds, 0, "Receive max coalcesced BDs");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_coal_ticks", CTLFLAG_RW,
	    &sc->ti_tx_coal_ticks, 0, "Send coalcesced ticks");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_max_coal_bds", CTLFLAG_RW,
	    &sc->ti_tx_max_coal_bds, 0, "Send max coalcesced BDs");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tx_buf_ratio", CTLFLAG_RW,
	    &sc->ti_tx_buf_ratio, 0,
	    "Ratio of NIC memory devoted to TX buffer");

	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "stat_ticks", CTLFLAG_RW,
	    &sc->ti_stat_ticks, 0,
	    "Number of clock ticks for statistics update interval");

	/* Pull in device tunables. */
	sc->ti_rx_coal_ticks = 170;
	resource_int_value(device_get_name(sc->ti_dev),
	    device_get_unit(sc->ti_dev), "rx_coal_ticks",
	    &sc->ti_rx_coal_ticks);
	sc->ti_rx_max_coal_bds = 64;
	resource_int_value(device_get_name(sc->ti_dev),
	    device_get_unit(sc->ti_dev), "rx_max_coal_bds",
	    &sc->ti_rx_max_coal_bds);

	sc->ti_tx_coal_ticks = TI_TICKS_PER_SEC / 500;
	resource_int_value(device_get_name(sc->ti_dev),
	    device_get_unit(sc->ti_dev), "tx_coal_ticks",
	    &sc->ti_tx_coal_ticks);
	sc->ti_tx_max_coal_bds = 32;
	resource_int_value(device_get_name(sc->ti_dev),
	    device_get_unit(sc->ti_dev), "tx_max_coal_bds",
	    &sc->ti_tx_max_coal_bds);
	sc->ti_tx_buf_ratio = 21;
	resource_int_value(device_get_name(sc->ti_dev),
	    device_get_unit(sc->ti_dev), "tx_buf_ratio",
	    &sc->ti_tx_buf_ratio);

	sc->ti_stat_ticks = 2 * TI_TICKS_PER_SEC;
	resource_int_value(device_get_name(sc->ti_dev),
	    device_get_unit(sc->ti_dev), "stat_ticks",
	    &sc->ti_stat_ticks);
}