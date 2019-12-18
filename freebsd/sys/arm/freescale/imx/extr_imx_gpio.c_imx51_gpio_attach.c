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
struct imx51_gpio_softc {int gpio_npins; int /*<<< orphan*/ * sc_busdev; TYPE_1__* gpio_pins; int /*<<< orphan*/ * gpio_ih; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_ioh; int /*<<< orphan*/  sc_iot; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; int /*<<< orphan*/  gp_name; int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CAPS ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  GPIO_PIN_INPUT ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  IMX_GPIO_IMR_REG ; 
 int /*<<< orphan*/  IMX_GPIO_OE_REG ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int NGPIO ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 unsigned int READ4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct imx51_gpio_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_pic_filter ; 
 int /*<<< orphan*/  gpio_pic_register_isrcs (struct imx51_gpio_softc*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx51_gpio_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_gpio_spec ; 
 int /*<<< orphan*/  intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
imx51_gpio_attach(device_t dev)
{
	struct imx51_gpio_softc *sc;
	int i, irq, unit;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->gpio_npins = NGPIO;

	mtx_init(&sc->sc_mtx, device_get_nameunit(sc->dev), NULL, MTX_SPIN);

	if (bus_alloc_resources(dev, imx_gpio_spec, sc->sc_res)) {
		device_printf(dev, "could not allocate resources\n");
		bus_release_resources(dev, imx_gpio_spec, sc->sc_res);
		mtx_destroy(&sc->sc_mtx);
		return (ENXIO);
	}

	sc->sc_iot = rman_get_bustag(sc->sc_res[0]);
	sc->sc_ioh = rman_get_bushandle(sc->sc_res[0]);
	/*
	 * Mask off all interrupts in hardware, then set up interrupt handling.
	 */
	WRITE4(sc, IMX_GPIO_IMR_REG, 0);
	for (irq = 0; irq < 2; irq++) {
#ifdef INTRNG
		if ((bus_setup_intr(dev, sc->sc_res[1 + irq], INTR_TYPE_CLK,
		    gpio_pic_filter, NULL, sc, &sc->gpio_ih[irq]))) {
			device_printf(dev,
			    "WARNING: unable to register interrupt handler\n");
			imx51_gpio_detach(dev);
			return (ENXIO);
		}
#endif		
	}

	unit = device_get_unit(dev);
	for (i = 0; i < sc->gpio_npins; i++) {
 		sc->gpio_pins[i].gp_pin = i;
 		sc->gpio_pins[i].gp_caps = DEFAULT_CAPS;
 		sc->gpio_pins[i].gp_flags =
 		    (READ4(sc, IMX_GPIO_OE_REG) & (1U << i)) ? GPIO_PIN_OUTPUT :
 		    GPIO_PIN_INPUT;
 		snprintf(sc->gpio_pins[i].gp_name, GPIOMAXNAME,
 		    "GPIO%d_IO%02d", unit + 1, i);
	}

#ifdef INTRNG
	gpio_pic_register_isrcs(sc);
	intr_pic_register(dev, OF_xref_from_node(ofw_bus_get_node(dev)));
#endif
	sc->sc_busdev = gpiobus_attach_bus(dev);
	
	if (sc->sc_busdev == NULL) {
		imx51_gpio_detach(dev);
		return (ENXIO);
	}

	return (0);
}