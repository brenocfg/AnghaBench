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
struct aw_ts_softc {int temp_offset; int temp_step; int /*<<< orphan*/  temp_data; int /*<<< orphan*/ * res; int /*<<< orphan*/  intrhand; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ocd_data; } ;

/* Variables and functions */
#define  A10_TS 129 
#define  A13_TS 128 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_CTRL0 ; 
 int TP_CTRL0_CLK_DIV (int) ; 
 int TP_CTRL0_CLK_SELECT (int /*<<< orphan*/ ) ; 
 int TP_CTRL0_FS_DIV (int) ; 
 int TP_CTRL0_TACQ (int) ; 
 int /*<<< orphan*/  TP_CTRL1 ; 
 int TP_CTRL1_MODE_EN ; 
 int /*<<< orphan*/  TP_FIFOC ; 
 int TP_FIFOC_TEMP_IRQ_ENABLE ; 
 int /*<<< orphan*/  TP_TPR ; 
 int TP_TPR_TEMP_EN ; 
 int TP_TPR_TEMP_PERIOD (int) ; 
 int /*<<< orphan*/  WRITE (struct aw_ts_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aw_ts_intr ; 
 int /*<<< orphan*/  aw_ts_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aw_ts_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_data ; 
 struct aw_ts_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_handle_int ; 

__attribute__((used)) static int
aw_ts_attach(device_t dev)
{
	struct aw_ts_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, aw_ts_spec, sc->res) != 0) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	if (bus_setup_intr(dev, sc->res[1],
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, aw_ts_intr, sc,
	    &sc->intrhand)) {
		bus_release_resources(dev, aw_ts_spec, sc->res);
		device_printf(dev, "cannot setup interrupt handler\n");
		return (ENXIO);
	}

	/*
	 * Thoses magic values were taken from linux which take them from
	 * the allwinner SDK or found them by deduction
	 */
	switch (ofw_bus_search_compatible(dev, compat_data)->ocd_data) {
	case A10_TS:
		sc->temp_offset = 257000;
		sc->temp_step = 133;
		break;
	case A13_TS:
		sc->temp_offset = 144700;
		sc->temp_step = 100;
		break;
	}

	/* Enable clock and set divisers */
	WRITE(sc, TP_CTRL0, TP_CTRL0_CLK_SELECT(0) |
	  TP_CTRL0_CLK_DIV(2) |
	  TP_CTRL0_FS_DIV(7) |
	  TP_CTRL0_TACQ(63));

	/* Enable TS module */
	WRITE(sc, TP_CTRL1, TP_CTRL1_MODE_EN);

	/* Enable Temperature, period is ~2s */
	WRITE(sc, TP_TPR, TP_TPR_TEMP_EN | TP_TPR_TEMP_PERIOD(1953));

	/* Enable temp irq */
	WRITE(sc, TP_FIFOC, TP_FIFOC_TEMP_IRQ_ENABLE);

	/* Add sysctl */
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "temperature", CTLTYPE_INT | CTLFLAG_RD,
	    &sc->temp_data, 0, sysctl_handle_int,
	    "IK3", "CPU Temperature");

	return (0);
}