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
struct dwgpio_softc {int port; int gpio_npins; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * busdev; TYPE_1__* gpio_pins; int /*<<< orphan*/  dev; int /*<<< orphan*/  node; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; int /*<<< orphan*/  gp_name; int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CAPS ; 
 int ENCODED_ID_PWIDTH_M ; 
 int ENCODED_ID_PWIDTH_S (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  GPIO_CONFIG_REG2 ; 
 int /*<<< orphan*/  GPIO_PIN_INPUT ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_SWPORT_DDR (int) ; 
 int /*<<< orphan*/  GPIO_VER_ID_CODE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int RB_VERBOSE ; 
 int READ4 (struct dwgpio_softc*,int /*<<< orphan*/ ) ; 
 int boothowto ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct dwgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
dwgpio_attach(device_t dev)
{
	struct dwgpio_softc *sc;
	int version;
	int nr_pins;
	int cfg2;
	int i;

	sc = device_get_softc(dev);
	sc->parent = device_get_parent(dev);
	sc->node = ofw_bus_get_node(dev);
	sc->dev = dev;
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	if ((OF_getencprop(sc->node, "reg", &sc->port, sizeof(sc->port))) <= 0)
		return (ENXIO);

	printf("port %d\n", sc->port);

	version =  READ4(sc, GPIO_VER_ID_CODE);
	if (boothowto & RB_VERBOSE)
		device_printf(sc->dev, "Version = 0x%08x\n", version);

	/* Grab number of pins from hardware. */
	cfg2 = READ4(sc, GPIO_CONFIG_REG2);
	nr_pins = (cfg2 >> ENCODED_ID_PWIDTH_S(sc->port)) & \
			ENCODED_ID_PWIDTH_M;
	sc->gpio_npins = nr_pins + 1;

	for (i = 0; i < sc->gpio_npins; i++) {
		sc->gpio_pins[i].gp_pin = i;
		sc->gpio_pins[i].gp_caps = DEFAULT_CAPS;
		sc->gpio_pins[i].gp_flags =
		    (READ4(sc, GPIO_SWPORT_DDR(sc->port)) & (1 << i)) ?
		    GPIO_PIN_OUTPUT: GPIO_PIN_INPUT;
		snprintf(sc->gpio_pins[i].gp_name, GPIOMAXNAME,
		    "dwgpio%d.%d", device_get_unit(dev), i);
	}
	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL) {
		mtx_destroy(&sc->sc_mtx);
		return (ENXIO);
	}

	return (0);
}