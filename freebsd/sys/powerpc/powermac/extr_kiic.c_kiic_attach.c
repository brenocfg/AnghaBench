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
struct kiic_softc {int sc_regstep; int sc_node; int sc_i2c_base; int sc_irqrid; int /*<<< orphan*/  sc_iicbus; int /*<<< orphan*/  sc_ih; void* sc_irq; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/ * sc_reg; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  I2C_100kHz ; 
 int I2C_INT_ADDR ; 
 int I2C_INT_DATA ; 
 int I2C_INT_STOP ; 
 int /*<<< orphan*/  I2C_STDMODE ; 
 int /*<<< orphan*/  IER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  ISR ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int OF_child (int) ; 
 int OF_getencprop (int,char*,int*,int) ; 
 scalar_t__ OF_getprop (int,char*,...) ; 
 int /*<<< orphan*/  REV ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kiic_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct kiic_softc*,int) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct kiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kiic_intr ; 
 int kiic_readreg (struct kiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kiic_setmode (struct kiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kiic_setspeed (struct kiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kiic_writereg (struct kiic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
kiic_attach(device_t self)
{
	struct kiic_softc *sc = device_get_softc(self);
	int rid, rate;
	phandle_t node;
	char name[64];

	bzero(sc, sizeof(*sc));
	sc->sc_dev = self;
	
	node = ofw_bus_get_node(self);
	if (node == 0 || node == -1) {
		return (EINVAL);
	}

	rid = 0;
	sc->sc_reg = bus_alloc_resource_any(self, SYS_RES_MEMORY,
			&rid, RF_ACTIVE);
	if (sc->sc_reg == NULL) {
		return (ENOMEM);
	}

	if (OF_getencprop(node, "AAPL,i2c-rate", &rate, 4) != 4) {
		device_printf(self, "cannot get i2c-rate\n");
		return (ENXIO);
	}
	if (OF_getencprop(node, "AAPL,address-step", &sc->sc_regstep, 4) != 4) {
		device_printf(self, "unable to find i2c address step\n");
		return (ENXIO);
	}

	/*
	 * Some Keywest I2C devices have their children attached directly
	 * underneath them.  Some have a single 'iicbus' child with the
	 * devices underneath that.  Sort this out, and make sure that the
	 * OFW I2C layer has the correct node.
	 *
	 * Note: the I2C children of the Uninorth bridges have two ports.
	 *  In general, the port is designated in the 9th bit of the I2C
	 *  address. However, for kiic devices with children attached below
	 *  an i2c-bus node, the port is indicated in the 'reg' property
	 *  of the i2c-bus node.
	 */

	sc->sc_node = node;

	node = OF_child(node);
	if (OF_getprop(node, "name", name, sizeof(name)) > 0) {
		if (strcmp(name,"i2c-bus") == 0) {
			phandle_t reg;
			if (OF_getprop(node, "reg", &reg, sizeof(reg)) > 0)
				sc->sc_i2c_base = reg << 8;

			sc->sc_node = node;
		}
	}

	mtx_init(&sc->sc_mutex, "kiic", NULL, MTX_DEF);

	sc->sc_irq = bus_alloc_resource_any(self, SYS_RES_IRQ, &sc->sc_irqrid, 
	    RF_ACTIVE);
	bus_setup_intr(self, sc->sc_irq, INTR_TYPE_MISC | INTR_MPSAFE, NULL,
	    kiic_intr, sc, &sc->sc_ih);

	kiic_writereg(sc, ISR, kiic_readreg(sc, ISR));
	kiic_writereg(sc, STATUS, 0);
	kiic_writereg(sc, IER, 0);

	kiic_setmode(sc, I2C_STDMODE);
	kiic_setspeed(sc, I2C_100kHz);		/* XXX rate */
	
	kiic_writereg(sc, IER, I2C_INT_DATA | I2C_INT_ADDR | I2C_INT_STOP);

	if (bootverbose)
		device_printf(self, "Revision: %02X\n", kiic_readreg(sc, REV));

	/* Add the IIC bus layer */
	sc->sc_iicbus = device_add_child(self, "iicbus", -1);

	return (bus_generic_attach(self));
}