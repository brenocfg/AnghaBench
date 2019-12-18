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
struct gpioiic_softc {int scl_pin; int sda_pin; int /*<<< orphan*/  sc_busdev; int /*<<< orphan*/  sc_dev; } ;
struct gpiobus_ivar {int /*<<< orphan*/ * pins; } ;
typedef  int /*<<< orphan*/  pin ;
typedef  int phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 void* GPIOIIC_SCL_DFLT ; 
 void* GPIOIIC_SDA_DFLT ; 
 scalar_t__ OF_getencprop (int,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct gpioiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
gpioiic_attach(device_t dev)
{
	device_t		bitbang;
#ifdef FDT
	phandle_t		node;
	pcell_t			pin;
#endif
	struct gpiobus_ivar	*devi;
	struct gpioiic_softc	*sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_busdev = device_get_parent(dev);
	if (resource_int_value(device_get_name(dev),
		device_get_unit(dev), "scl", &sc->scl_pin))
		sc->scl_pin = GPIOIIC_SCL_DFLT;
	if (resource_int_value(device_get_name(dev),
		device_get_unit(dev), "sda", &sc->sda_pin))
		sc->sda_pin = GPIOIIC_SDA_DFLT;

#ifdef FDT
	if ((node = ofw_bus_get_node(dev)) == -1)
		return (ENXIO);
	if (OF_getencprop(node, "scl", &pin, sizeof(pin)) > 0)
		sc->scl_pin = (int)pin;
	if (OF_getencprop(node, "sda", &pin, sizeof(pin)) > 0)
		sc->sda_pin = (int)pin;
#endif

	if (sc->scl_pin < 0 || sc->scl_pin > 1)
		sc->scl_pin = GPIOIIC_SCL_DFLT;
	if (sc->sda_pin < 0 || sc->sda_pin > 1)
		sc->sda_pin = GPIOIIC_SDA_DFLT;

	devi = GPIOBUS_IVAR(dev);
	device_printf(dev, "SCL pin: %d, SDA pin: %d\n",
	    devi->pins[sc->scl_pin], devi->pins[sc->sda_pin]);

	/* add generic bit-banging code */
	bitbang = device_add_child(dev, "iicbb", -1);
	device_probe_and_attach(bitbang);

	return (0);
}