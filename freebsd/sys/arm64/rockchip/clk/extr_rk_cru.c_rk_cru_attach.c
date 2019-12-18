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
struct rk_cru_softc {int nclks; int /*<<< orphan*/ * clkdom; scalar_t__ gates; TYPE_2__* clks; int /*<<< orphan*/  mtx; int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  link; int /*<<< orphan*/  fract; int /*<<< orphan*/  fixed; int /*<<< orphan*/  armclk; int /*<<< orphan*/  mux; int /*<<< orphan*/  composite; int /*<<< orphan*/  pll; } ;
struct TYPE_4__ {int type; TYPE_1__ clk; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
#define  RK3328_CLK_PLL 136 
#define  RK3399_CLK_PLL 135 
#define  RK_CLK_ARMCLK 134 
#define  RK_CLK_COMPOSITE 133 
#define  RK_CLK_FIXED 132 
#define  RK_CLK_FRACT 131 
#define  RK_CLK_LINK 130 
#define  RK_CLK_MUX 129 
#define  RK_CLK_UNDEFINED 128 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_set_assigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clkdom_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_dump (int /*<<< orphan*/ *) ; 
 scalar_t__ clkdom_finit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_fixed_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clknode_link_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct rk_cru_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hwreset_register_ofw_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rk3328_clk_pll_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3399_clk_pll_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_clk_armclk_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_clk_composite_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_clk_fract_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_clk_mux_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_cru_register_gates (struct rk_cru_softc*) ; 
 int /*<<< orphan*/  rk_cru_spec ; 

int
rk_cru_attach(device_t dev)
{
	struct rk_cru_softc *sc;
	phandle_t node;
	int	i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	node = ofw_bus_get_node(dev);

	if (bus_alloc_resources(dev, rk_cru_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	sc->clkdom = clkdom_create(dev);
	if (sc->clkdom == NULL)
		panic("Cannot create clkdom\n");

	for (i = 0; i < sc->nclks; i++) {
		switch (sc->clks[i].type) {
		case RK_CLK_UNDEFINED:
			break;
		case RK3328_CLK_PLL:
			rk3328_clk_pll_register(sc->clkdom,
			    sc->clks[i].clk.pll);
			break;
		case RK3399_CLK_PLL:
			rk3399_clk_pll_register(sc->clkdom,
			    sc->clks[i].clk.pll);
			break;
		case RK_CLK_COMPOSITE:
			rk_clk_composite_register(sc->clkdom,
			    sc->clks[i].clk.composite);
			break;
		case RK_CLK_MUX:
			rk_clk_mux_register(sc->clkdom, sc->clks[i].clk.mux);
			break;
		case RK_CLK_ARMCLK:
			rk_clk_armclk_register(sc->clkdom,
			    sc->clks[i].clk.armclk);
			break;
		case RK_CLK_FIXED:
			clknode_fixed_register(sc->clkdom,
			    sc->clks[i].clk.fixed);
			break;
		case RK_CLK_FRACT:
			rk_clk_fract_register(sc->clkdom,
			    sc->clks[i].clk.fract);
			break;
		case RK_CLK_LINK:
			clknode_link_register(sc->clkdom,
			    sc->clks[i].clk.link);
			break;
		default:
			device_printf(dev, "Unknown clock type\n");
			return (ENXIO);
		}
	}

	if (sc->gates)
		rk_cru_register_gates(sc);

	if (clkdom_finit(sc->clkdom) != 0)
		panic("cannot finalize clkdom initialization\n");

	if (bootverbose)
		clkdom_dump(sc->clkdom);

	clk_set_assigned(dev, node);

	/* register our self as a reset provider */
	hwreset_register_ofw_provider(dev);

	return (0);
}