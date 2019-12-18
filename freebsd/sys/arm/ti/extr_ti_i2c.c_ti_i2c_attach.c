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
typedef  int uint16_t ;
struct ti_i2c_softc {scalar_t__ clk_id; int sc_rev; int sc_fifo_trsh; int sc_timeout; int /*<<< orphan*/ * sc_iicbus; int /*<<< orphan*/  sc_irq_h; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_dev; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ich_func_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_UINT ; 
 int ENXIO ; 
 int I2C_BUFSTAT_FIFODEPTH_MASK ; 
 int I2C_BUFSTAT_FIFODEPTH_SHIFT ; 
 int /*<<< orphan*/  I2C_REG_BUFSTAT ; 
 int /*<<< orphan*/  I2C_REG_REVNB_HI ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 scalar_t__ INVALID_CLK_IDENT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct ti_i2c_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_I2C_LOCK_DESTROY (struct ti_i2c_softc*) ; 
 int /*<<< orphan*/  TI_I2C_LOCK_INIT (struct ti_i2c_softc*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_generic_attach ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ti_i2c_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct ti_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hz ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ti_hwmods_get_clock (int /*<<< orphan*/ ) ; 
 int ti_i2c_activate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_i2c_deactivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_i2c_intr ; 
 int ti_i2c_read_2 (struct ti_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_i2c_sysctl_clk ; 
 int /*<<< orphan*/  ti_i2c_sysctl_timeout ; 

__attribute__((used)) static int
ti_i2c_attach(device_t dev)
{
	int err, rid;
	phandle_t node;
	struct ti_i2c_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *tree;
	uint16_t fifosz;

 	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	/* Get the i2c device id from FDT. */
	node = ofw_bus_get_node(dev);
	/* i2c ti,hwmods bindings is special: it start with index 1 */
	sc->clk_id = ti_hwmods_get_clock(dev);
	if (sc->clk_id == INVALID_CLK_IDENT) {
		device_printf(dev, "failed to get device id using ti,hwmod\n");
		return (ENXIO);
	}

	/* Get the memory resource for the register mapping. */
	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "Cannot map registers.\n");
		return (ENXIO);
	}

	/* Allocate our IRQ resource. */
	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->sc_irq_res == NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		device_printf(dev, "Cannot allocate interrupt.\n");
		return (ENXIO);
	}

	TI_I2C_LOCK_INIT(sc);

	/* First of all, we _must_ activate the H/W. */
	err = ti_i2c_activate(dev);
	if (err) {
		device_printf(dev, "ti_i2c_activate failed\n");
		goto out;
	}

	/* Read the version number of the I2C module */
	sc->sc_rev = ti_i2c_read_2(sc, I2C_REG_REVNB_HI) & 0xff;

	/* Get the fifo size. */
	fifosz = ti_i2c_read_2(sc, I2C_REG_BUFSTAT);
	fifosz >>= I2C_BUFSTAT_FIFODEPTH_SHIFT;
	fifosz &= I2C_BUFSTAT_FIFODEPTH_MASK;

	device_printf(dev, "I2C revision %d.%d FIFO size: %d bytes\n",
	    sc->sc_rev >> 4, sc->sc_rev & 0xf, 8 << fifosz);

	/* Set the FIFO threshold to 5 for now. */
	sc->sc_fifo_trsh = 5;

	/* Set I2C bus timeout */
	sc->sc_timeout = 5*hz;

	ctx = device_get_sysctl_ctx(dev);
	tree = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "i2c_clock",
	    CTLFLAG_RD | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ti_i2c_sysctl_clk, "IU", "I2C bus clock");

	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "i2c_timeout",
	    CTLFLAG_RW | CTLTYPE_UINT | CTLFLAG_MPSAFE, sc, 0,
	    ti_i2c_sysctl_timeout, "IU", "I2C bus timeout (in ticks)");

	/* Activate the interrupt. */
	err = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, ti_i2c_intr, sc, &sc->sc_irq_h);
	if (err)
		goto out;

	/* Attach the iicbus. */
	if ((sc->sc_iicbus = device_add_child(dev, "iicbus", -1)) == NULL) {
		device_printf(dev, "could not allocate iicbus instance\n");
		err = ENXIO;
		goto out;
	}

	/* Probe and attach the iicbus when interrupts are available. */
	config_intrhook_oneshot((ich_func_t)bus_generic_attach, dev);

out:
	if (err) {
		ti_i2c_deactivate(dev);
		TI_I2C_LOCK_DESTROY(sc);
	}

	return (err);
}