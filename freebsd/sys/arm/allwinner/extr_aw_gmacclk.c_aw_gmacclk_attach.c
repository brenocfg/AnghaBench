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
struct clknode_init_def {int id; int parent_cnt; int /*<<< orphan*/ * parent_names; int /*<<< orphan*/  name; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct aw_gmacclk_sc {int tx_delay; int rx_delay; int /*<<< orphan*/  clkdev; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  def ;
typedef  int /*<<< orphan*/  clk_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int CLK_IDX_COUNT ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  aw_gmacclk_clknode_class ; 
 scalar_t__ bootverbose ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 int clk_parse_ofw_clk_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ ) ; 
 struct clkdom* clkdom_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_dump (struct clkdom*) ; 
 scalar_t__ clkdom_finit (struct clkdom*) ; 
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,struct clknode_init_def*) ; 
 struct aw_gmacclk_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct clknode_init_def*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_parse_xref_list_get_length (int /*<<< orphan*/ ,char*,char*,int*) ; 
 scalar_t__ ofw_reg_to_paddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aw_gmacclk_attach(device_t dev)
{
	struct clknode_init_def def;
	struct aw_gmacclk_sc *sc;
	struct clkdom *clkdom;
	struct clknode *clk;
	clk_t clk_parent;
	bus_addr_t paddr;
	bus_size_t psize;
	phandle_t node;
	int error, ncells, i;

	node = ofw_bus_get_node(dev);

	if (ofw_reg_to_paddr(node, 0, &paddr, &psize, NULL) != 0) {
		device_printf(dev, "cannot parse 'reg' property\n");
		return (ENXIO);
	}

	error = ofw_bus_parse_xref_list_get_length(node, "clocks",
	    "#clock-cells", &ncells);
	if (error != 0 || ncells != CLK_IDX_COUNT) {
		device_printf(dev, "couldn't find parent clocks\n");
		return (ENXIO);
	}

	clkdom = clkdom_create(dev);

	memset(&def, 0, sizeof(def));
	error = clk_parse_ofw_clk_name(dev, node, &def.name);
	if (error != 0) {
		device_printf(dev, "cannot parse clock name\n");
		error = ENXIO;
		goto fail;
	}
	def.id = 1;
	def.parent_names = malloc(sizeof(char *) * ncells, M_OFWPROP, M_WAITOK);
	for (i = 0; i < ncells; i++) {
		error = clk_get_by_ofw_index(dev, 0, i, &clk_parent);
		if (error != 0) {
			device_printf(dev, "cannot get clock %d\n", error);
			goto fail;
		}
		def.parent_names[i] = clk_get_name(clk_parent);
		clk_release(clk_parent);
	}
	def.parent_cnt = ncells;

	clk = clknode_create(clkdom, &aw_gmacclk_clknode_class, &def);
	if (clk == NULL) {
		device_printf(dev, "cannot create clknode\n");
		error = ENXIO;
		goto fail;
	}

	sc = clknode_get_softc(clk);
	sc->reg = paddr;
	sc->clkdev = device_get_parent(dev);
	sc->tx_delay = sc->rx_delay = -1;
	OF_getencprop(node, "tx-delay", &sc->tx_delay, sizeof(sc->tx_delay));
	OF_getencprop(node, "rx-delay", &sc->rx_delay, sizeof(sc->rx_delay));

	clknode_register(clkdom, clk);

	if (clkdom_finit(clkdom) != 0) {
		device_printf(dev, "cannot finalize clkdom initialization\n");
		error = ENXIO;
		goto fail;
	}

	if (bootverbose)
		clkdom_dump(clkdom);

	return (0);

fail:
	return (error);
}