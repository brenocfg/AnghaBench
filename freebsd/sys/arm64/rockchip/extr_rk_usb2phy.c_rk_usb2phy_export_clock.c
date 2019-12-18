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
struct rk_usb2phy_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  grf; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct rk_usb2phy_regs {TYPE_1__ clk_ctl; } ;
struct rk_usb2phy_clk_sc {struct rk_usb2phy_regs* regs; int /*<<< orphan*/  grf; int /*<<< orphan*/  clkdev; } ;
struct clknode_init_def {char const* name; int parent_cnt; int /*<<< orphan*/ * parent_names; scalar_t__ id; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
typedef  int /*<<< orphan*/  regs ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  def ;
typedef  int /*<<< orphan*/  clk_t ;
struct TYPE_4__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bootverbose ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ ) ; 
 struct clkdom* clkdom_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_dump (struct clkdom*) ; 
 scalar_t__ clkdom_finit (struct clkdom*) ; 
 int /*<<< orphan*/  clkdom_set_ofw_mapper (struct clkdom*,int /*<<< orphan*/ ) ; 
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,struct clknode_init_def*) ; 
 struct rk_usb2phy_clk_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct clknode_init_def*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_parse_xref_list_get_length (int /*<<< orphan*/ ,char*,char*,int*) ; 
 TYPE_2__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofw_bus_string_list_to_array (int /*<<< orphan*/ ,char*,char const***) ; 
 int /*<<< orphan*/  rk_usb2phy_clk_clknode_class ; 
 int /*<<< orphan*/  rk_usb2phy_clk_ofw_map ; 

__attribute__((used)) static int
rk_usb2phy_export_clock(struct rk_usb2phy_softc *devsc)
{
	struct clknode_init_def def;
	struct rk_usb2phy_clk_sc *sc;
	const char **clknames;
	struct clkdom *clkdom;
	struct clknode *clk;
	clk_t clk_parent;
	phandle_t node;
	phandle_t regs[2];
	int i, nclocks, ncells, error;

	node = ofw_bus_get_node(devsc->dev);

	error = ofw_bus_parse_xref_list_get_length(node, "clocks",
	    "#clock-cells", &ncells);
	if (error != 0 || ncells != 1) {
		device_printf(devsc->dev, "couldn't find parent clock\n");
		return (ENXIO);
	}

	nclocks = ofw_bus_string_list_to_array(node, "clock-output-names",
	    &clknames);
	if (nclocks != 1)
		return (ENXIO);

	clkdom = clkdom_create(devsc->dev);
	clkdom_set_ofw_mapper(clkdom, rk_usb2phy_clk_ofw_map);

	memset(&def, 0, sizeof(def));
	def.id = 0;
	def.name = clknames[0];
	def.parent_names = malloc(sizeof(char *) * ncells, M_OFWPROP, M_WAITOK);
	for (i = 0; i < ncells; i++) {
		error = clk_get_by_ofw_index(devsc->dev, 0, i, &clk_parent);
		if (error != 0) {
			device_printf(devsc->dev, "cannot get clock %d\n", error);
			return (ENXIO);
		}
		def.parent_names[i] = clk_get_name(clk_parent);
		clk_release(clk_parent);
	}
	def.parent_cnt = ncells;

	clk = clknode_create(clkdom, &rk_usb2phy_clk_clknode_class, &def);
	if (clk == NULL) {
		device_printf(devsc->dev, "cannot create clknode\n");
		return (ENXIO);
	}

	sc = clknode_get_softc(clk);
	sc->clkdev = device_get_parent(devsc->dev);
	sc->grf = devsc->grf;
	sc->regs = (struct rk_usb2phy_regs *)ofw_bus_search_compatible(devsc->dev, compat_data)->ocd_data;
	OF_getencprop(node, "reg", regs, sizeof(regs));
	sc->regs->clk_ctl.offset = regs[0];
	clknode_register(clkdom, clk);

	if (clkdom_finit(clkdom) != 0) {
		device_printf(devsc->dev, "cannot finalize clkdom initialization\n");
		return (ENXIO);
	}

	if (bootverbose)
		clkdom_dump(clkdom);

	return (0);
}