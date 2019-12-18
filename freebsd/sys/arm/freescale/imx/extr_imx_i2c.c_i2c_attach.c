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
typedef  int /*<<< orphan*/  wrkstr ;
struct i2c_softc {int rb_pinctl_idx; int /*<<< orphan*/  rb_sdapin; int /*<<< orphan*/  rb_sclpin; int /*<<< orphan*/  dev; int /*<<< orphan*/  debug; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/ * res; scalar_t__ rid; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ich_func_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_generic_attach ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int gpio_pin_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_pin_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_pin_setflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofw_bus_find_string_index (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
i2c_attach(device_t dev)
{
	char wrkstr[16];
	struct i2c_softc *sc;
	phandle_t node;
	int err, cfgidx;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->rid = 0;

	sc->res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->rid,
	    RF_ACTIVE);
	if (sc->res == NULL) {
		device_printf(dev, "could not allocate resources");
		return (ENXIO);
	}

	sc->iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(dev, "could not add iicbus child");
		return (ENXIO);
	}

	/* Set up debug-enable sysctl. */
	SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->dev), 
	    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)),
	    OID_AUTO, "debug", CTLFLAG_RWTUN, &sc->debug, 0,
	    "Enable debug; 1=reads/writes, 2=add starts/stops");

	/*
	 * Set up for bus recovery using gpio pins, if the pinctrl and gpio
	 * properties are present.  This is optional.  If all the config data is
	 * not in place, we just don't do gpio bitbang bus recovery.
	 */
	node = ofw_bus_get_node(sc->dev);

	err = gpio_pin_get_by_ofw_property(dev, node, "scl-gpios",
	    &sc->rb_sclpin);
	if (err != 0)
		goto no_recovery;
	err = gpio_pin_get_by_ofw_property(dev, node, "sda-gpios",
	    &sc->rb_sdapin);
	if (err != 0)
		goto no_recovery;

	/*
	 * Preset the gpio pins to output high (idle bus state).  The signal
	 * won't actually appear on the pins until the bus recovery code changes
	 * the pinmux config from i2c to gpio.
	 */
	gpio_pin_setflags(sc->rb_sclpin, GPIO_PIN_OUTPUT);
	gpio_pin_setflags(sc->rb_sdapin, GPIO_PIN_OUTPUT);
	gpio_pin_set_active(sc->rb_sclpin, true);
	gpio_pin_set_active(sc->rb_sdapin, true);

	/*
	 * Obtain the index of pinctrl node for bus recovery using gpio pins,
	 * then confirm that pinctrl properties exist for that index and for the
	 * default pinctrl-0.  If sc->rb_pinctl_idx is non-zero, the reset code
	 * will also do a bus recovery, so setting this value must be last.
	 */
	err = ofw_bus_find_string_index(node, "pinctrl-names", "gpio", &cfgidx);
	if (err == 0) {
		snprintf(wrkstr, sizeof(wrkstr), "pinctrl-%d", cfgidx);
		if (OF_hasprop(node, "pinctrl-0") && OF_hasprop(node, wrkstr))
			sc->rb_pinctl_idx = cfgidx;
	}

no_recovery:

	/* We don't do a hardware reset here because iicbus_attach() does it. */

	/* Probe and attach the iicbus when interrupts are available. */
	config_intrhook_oneshot((ich_func_t)bus_generic_attach, dev);
	return (0);
}