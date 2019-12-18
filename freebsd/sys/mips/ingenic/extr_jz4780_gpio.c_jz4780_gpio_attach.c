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
typedef  size_t uint32_t ;
struct jz4780_gpio_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/ * intrhand; int /*<<< orphan*/ * busdev; TYPE_1__* pins; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pu_pins ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pd_pins ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {size_t pin_num; int pin_caps; char* pin_name; int /*<<< orphan*/  intr_trigger; int /*<<< orphan*/  intr_polarity; } ;

/* Variables and functions */
 int ENXIO ; 
 int GPIOMAXNAME ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_PULLDOWN ; 
 int GPIO_PIN_PULLUP ; 
 int INTR_MPSAFE ; 
 int /*<<< orphan*/  INTR_POLARITY_CONFORM ; 
 int /*<<< orphan*/  INTR_TRIGGER_CONFORM ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  JZ4780_GPIO_LOCK_DESTROY (struct jz4780_gpio_softc*) ; 
 int /*<<< orphan*/  JZ4780_GPIO_LOCK_INIT (struct jz4780_gpio_softc*) ; 
 size_t JZ4780_GPIO_PINS ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,size_t*,int) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct jz4780_gpio_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct jz4780_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_gpio_intr ; 
 int /*<<< orphan*/  jz4780_gpio_pin_probe (struct jz4780_gpio_softc*,size_t) ; 
 scalar_t__ jz4780_gpio_register_isrcs (struct jz4780_gpio_softc*) ; 
 int /*<<< orphan*/  jz4780_gpio_spec ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,size_t) ; 

__attribute__((used)) static int
jz4780_gpio_attach(device_t dev)
{
	struct jz4780_gpio_softc *sc = device_get_softc(dev);
	phandle_t node;
	uint32_t i, pd_pins, pu_pins;

	sc->dev = dev;

	if (bus_alloc_resources(dev, jz4780_gpio_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	JZ4780_GPIO_LOCK_INIT(sc);

	node = ofw_bus_get_node(dev);
	OF_getencprop(node, "ingenic,pull-ups", &pu_pins, sizeof(pu_pins));
	OF_getencprop(node, "ingenic,pull-downs", &pd_pins, sizeof(pd_pins));

	for (i = 0; i < JZ4780_GPIO_PINS; i++) {
		sc->pins[i].pin_num = i;
		sc->pins[i].pin_caps |= GPIO_PIN_INPUT | GPIO_PIN_OUTPUT;
		if (pu_pins & (1 << i))
			sc->pins[i].pin_caps |= GPIO_PIN_PULLUP;
		if (pd_pins & (1 << i))
			sc->pins[i].pin_caps |= GPIO_PIN_PULLDOWN;
		sc->pins[i].intr_polarity = INTR_POLARITY_CONFORM;
		sc->pins[i].intr_trigger = INTR_TRIGGER_CONFORM;

		snprintf(sc->pins[i].pin_name, GPIOMAXNAME - 1, "gpio%c%d",
		    device_get_unit(dev) + 'a', i);
		sc->pins[i].pin_name[GPIOMAXNAME - 1] = '\0';

		jz4780_gpio_pin_probe(sc, i);
	}

	if (jz4780_gpio_register_isrcs(sc) != 0)
		goto fail;

	if (intr_pic_register(dev, OF_xref_from_node(node)) == NULL) {
		device_printf(dev, "could not register PIC\n");
		goto fail;
	}

	if (bus_setup_intr(dev, sc->res[1], INTR_TYPE_MISC | INTR_MPSAFE,
	    jz4780_gpio_intr, NULL, sc, &sc->intrhand) != 0)
		goto fail_pic;

	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL)
		goto fail_pic;

	return (0);
fail_pic:
	intr_pic_deregister(dev, OF_xref_from_node(node));
fail:
	if (sc->intrhand != NULL)
		bus_teardown_intr(dev, sc->res[1], sc->intrhand);
	bus_release_resources(dev, jz4780_gpio_spec, sc->res);
	JZ4780_GPIO_LOCK_DESTROY(sc);
	return (ENXIO);
}