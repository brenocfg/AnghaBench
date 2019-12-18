#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aw_ccung_softc {int nclks; scalar_t__ resets; int /*<<< orphan*/ * clkdom; scalar_t__ gates; TYPE_2__* clks; int /*<<< orphan*/  mtx; int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  nmm; int /*<<< orphan*/  np; int /*<<< orphan*/  mipi; int /*<<< orphan*/  frac; int /*<<< orphan*/  prediv_mux; int /*<<< orphan*/  m; int /*<<< orphan*/  nm; int /*<<< orphan*/  nkmp; int /*<<< orphan*/  fixed; int /*<<< orphan*/  div; int /*<<< orphan*/  mux; } ;
struct TYPE_4__ {int type; TYPE_1__ clk; } ;

/* Variables and functions */
#define  AW_CLK_DIV 139 
#define  AW_CLK_FIXED 138 
#define  AW_CLK_FRAC 137 
#define  AW_CLK_M 136 
#define  AW_CLK_MIPI 135 
#define  AW_CLK_MUX 134 
#define  AW_CLK_NKMP 133 
#define  AW_CLK_NM 132 
#define  AW_CLK_NMM 131 
#define  AW_CLK_NP 130 
#define  AW_CLK_PREDIV_MUX 129 
#define  AW_CLK_UNDEFINED 128 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  aw_ccung_init_clocks (struct aw_ccung_softc*) ; 
 int /*<<< orphan*/  aw_ccung_register_gates (struct aw_ccung_softc*) ; 
 int /*<<< orphan*/  aw_ccung_spec ; 
 int /*<<< orphan*/  aw_clk_frac_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_clk_m_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_clk_mipi_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_clk_nkmp_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_clk_nm_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_clk_nmm_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_clk_np_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_clk_prediv_mux_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clkdom_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_dump (int /*<<< orphan*/ *) ; 
 scalar_t__ clkdom_finit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clkdom_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clkdom_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_div_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clknode_fixed_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clknode_mux_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct aw_ccung_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hwreset_register_ofw_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
aw_ccung_attach(device_t dev)
{
	struct aw_ccung_softc *sc;
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, aw_ccung_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	sc->clkdom = clkdom_create(dev);
	if (sc->clkdom == NULL)
		panic("Cannot create clkdom\n");

	for (i = 0; i < sc->nclks; i++) {
		switch (sc->clks[i].type) {
		case AW_CLK_UNDEFINED:
			break;
		case AW_CLK_MUX:
			clknode_mux_register(sc->clkdom, sc->clks[i].clk.mux);
			break;
		case AW_CLK_DIV:
			clknode_div_register(sc->clkdom, sc->clks[i].clk.div);
			break;
		case AW_CLK_FIXED:
			clknode_fixed_register(sc->clkdom,
			    sc->clks[i].clk.fixed);
			break;
		case AW_CLK_NKMP:
			aw_clk_nkmp_register(sc->clkdom, sc->clks[i].clk.nkmp);
			break;
		case AW_CLK_NM:
			aw_clk_nm_register(sc->clkdom, sc->clks[i].clk.nm);
			break;
		case AW_CLK_M:
			aw_clk_m_register(sc->clkdom, sc->clks[i].clk.m);
			break;
		case AW_CLK_PREDIV_MUX:
			aw_clk_prediv_mux_register(sc->clkdom,
			    sc->clks[i].clk.prediv_mux);
			break;
		case AW_CLK_FRAC:
			aw_clk_frac_register(sc->clkdom, sc->clks[i].clk.frac);
			break;
		case AW_CLK_MIPI:
			aw_clk_mipi_register(sc->clkdom, sc->clks[i].clk.mipi);
			break;
		case AW_CLK_NP:
			aw_clk_np_register(sc->clkdom, sc->clks[i].clk.np);
			break;
		case AW_CLK_NMM:
			aw_clk_nmm_register(sc->clkdom, sc->clks[i].clk.nmm);
			break;
		}
	}

	if (sc->gates)
		aw_ccung_register_gates(sc);
	if (clkdom_finit(sc->clkdom) != 0)
		panic("cannot finalize clkdom initialization\n");

	clkdom_xlock(sc->clkdom);
	aw_ccung_init_clocks(sc);
	clkdom_unlock(sc->clkdom);

	if (bootverbose)
		clkdom_dump(sc->clkdom);

	/* If we have resets, register our self as a reset provider */
	if (sc->resets)
		hwreset_register_ofw_provider(dev);

	return (0);
}