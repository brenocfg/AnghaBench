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
struct mtk_gpio_softc {size_t num_pins; int /*<<< orphan*/ * res; int /*<<< orphan*/ * intrhand; int /*<<< orphan*/ * busdev; TYPE_1__* pins; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  num_pins ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int pin_caps; char* pin_name; int /*<<< orphan*/  intr_trigger; int /*<<< orphan*/  intr_polarity; } ;

/* Variables and functions */
 int ENXIO ; 
 int GPIOMAXNAME ; 
 int GPIO_INTR_EDGE_FALLING ; 
 int GPIO_INTR_EDGE_RISING ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_INVIN ; 
 int GPIO_PIN_INVOUT ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIOMAX ; 
 int INTR_MPSAFE ; 
 int /*<<< orphan*/  INTR_POLARITY_HIGH ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTK_GPIO_LOCK_DESTROY (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_GPIO_LOCK_INIT (struct mtk_gpio_softc*) ; 
 size_t MTK_GPIO_PINS ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,size_t*,int) ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mtk_gpio_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mtk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_gpio_intr ; 
 int /*<<< orphan*/  mtk_gpio_pin_probe (struct mtk_gpio_softc*,size_t) ; 
 int /*<<< orphan*/  mtk_gpio_spec ; 
 scalar_t__ mtk_pic_register_isrcs (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  mtk_soc_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_soc_start_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,size_t) ; 

__attribute__((used)) static int
mtk_gpio_attach(device_t dev)
{
	struct mtk_gpio_softc *sc;
	phandle_t node;
	uint32_t i, num_pins;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, mtk_gpio_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	MTK_GPIO_LOCK_INIT(sc);

	node = ofw_bus_get_node(dev);

	if (OF_hasprop(node, "clocks"))
		mtk_soc_start_clock(dev);
	if (OF_hasprop(node, "resets"))
		mtk_soc_reset_device(dev);

	if (OF_getprop(node, "ralink,register-map", sc->regs,
	    GPIO_PIOMAX) <= 0) {
		device_printf(dev, "Failed to read register map\n");
		return (ENXIO);
	}

	if (OF_hasprop(node, "ralink,num-gpios") && (OF_getencprop(node,
	    "ralink,num-gpios", &num_pins, sizeof(num_pins)) >= 0))
		sc->num_pins = num_pins;
	else
		sc->num_pins = MTK_GPIO_PINS;

	for (i = 0; i < sc->num_pins; i++) {
		sc->pins[i].pin_caps |= GPIO_PIN_INPUT | GPIO_PIN_OUTPUT |
		    GPIO_PIN_INVIN | GPIO_PIN_INVOUT |
		    GPIO_INTR_EDGE_RISING | GPIO_INTR_EDGE_FALLING;
		sc->pins[i].intr_polarity = INTR_POLARITY_HIGH;
		sc->pins[i].intr_trigger = INTR_TRIGGER_EDGE;

		snprintf(sc->pins[i].pin_name, GPIOMAXNAME - 1, "gpio%c%d",
		    device_get_unit(dev) + 'a', i);
		sc->pins[i].pin_name[GPIOMAXNAME - 1] = '\0';

		mtk_gpio_pin_probe(sc, i);
	}

	if (mtk_pic_register_isrcs(sc) != 0) {
		device_printf(dev, "could not register PIC ISRCs\n");
		goto fail;
	}

	if (intr_pic_register(dev, OF_xref_from_node(node)) == NULL) {
		device_printf(dev, "could not register PIC\n");
		goto fail;
	}

	if (bus_setup_intr(dev, sc->res[1], INTR_TYPE_MISC | INTR_MPSAFE,
	    mtk_gpio_intr, NULL, sc, &sc->intrhand) != 0)
		goto fail_pic;

	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL)
		goto fail_pic;

	return (0);
fail_pic:
	intr_pic_deregister(dev, OF_xref_from_node(node));
fail:
	if(sc->intrhand != NULL)
		bus_teardown_intr(dev, sc->res[1], sc->intrhand);
	bus_release_resources(dev, mtk_gpio_spec, sc->res);
	MTK_GPIO_LOCK_DESTROY(sc);
	return (ENXIO);
}