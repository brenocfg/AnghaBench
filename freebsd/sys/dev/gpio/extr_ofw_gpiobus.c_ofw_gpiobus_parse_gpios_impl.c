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
struct gpiobus_softc {int /*<<< orphan*/  sc_busdev; int /*<<< orphan*/  sc_dev; } ;
struct gpiobus_pin {int /*<<< orphan*/  pin; int /*<<< orphan*/  flags; int /*<<< orphan*/ * dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  gpiocells ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GPIO_GET_BUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * OF_device_from_xref (scalar_t__) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 int OF_getencprop_alloc_multi (scalar_t__,char*,int,void**) ; 
 int /*<<< orphan*/  OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_node_from_xref (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (scalar_t__*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct gpiobus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct gpiobus_pin*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_map_gpios (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gpiobus_acquire_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpiobus_pin* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_gpiobus_parse_gpios_impl(device_t consumer, phandle_t cnode, char *pname,
	struct gpiobus_softc *bussc, struct gpiobus_pin **pins)
{
	int gpiocells, i, j, ncells, npins;
	pcell_t *gpios;
	phandle_t gpio;

	ncells = OF_getencprop_alloc_multi(cnode, pname, sizeof(*gpios),
            (void **)&gpios);
	if (ncells == -1) {
		device_printf(consumer,
		    "Warning: No %s specified in fdt data; "
		    "device may not function.\n", pname);
		return (-1);
	}
	/*
	 * The gpio-specifier is controller independent, the first pcell has
	 * the reference to the GPIO controller phandler.
	 * Count the number of encoded gpio-specifiers on the first pass.
	 */
	i = 0;
	npins = 0;
	while (i < ncells) {
		/* Allow NULL specifiers. */
		if (gpios[i] == 0) {
			npins++;
			i++;
			continue;
		}
		gpio = OF_node_from_xref(gpios[i]);
		/* If we have bussc, ignore devices from other gpios. */
		if (bussc != NULL)
			if (ofw_bus_get_node(bussc->sc_dev) != gpio)
				return (0);
		/*
		 * Check for gpio-controller property and read the #gpio-cells
		 * for this GPIO controller.
		 */
		if (!OF_hasprop(gpio, "gpio-controller") ||
		    OF_getencprop(gpio, "#gpio-cells", &gpiocells,
		    sizeof(gpiocells)) < 0) {
			device_printf(consumer,
			    "gpio reference is not a gpio-controller.\n");
			OF_prop_free(gpios);
			return (-1);
		}
		if (ncells - i < gpiocells + 1) {
			device_printf(consumer,
			    "%s cells doesn't match #gpio-cells.\n", pname);
			return (-1);
		}
		npins++;
		i += gpiocells + 1;
	}
	if (npins == 0 || pins == NULL) {
		if (npins == 0)
			device_printf(consumer, "no pin specified in %s.\n",
			    pname);
		OF_prop_free(gpios);
		return (npins);
	}
	*pins = malloc(sizeof(struct gpiobus_pin) * npins, M_DEVBUF,
	    M_NOWAIT | M_ZERO);
	if (*pins == NULL) {
		OF_prop_free(gpios);
		return (-1);
	}
	/* Decode the gpio specifier on the second pass. */
	i = 0;
	j = 0;
	while (i < ncells) {
		/* Allow NULL specifiers. */
		if (gpios[i] == 0) {
			j++;
			i++;
			continue;
		}
		gpio = OF_node_from_xref(gpios[i]);
		/* Read gpio-cells property for this GPIO controller. */
		if (OF_getencprop(gpio, "#gpio-cells", &gpiocells,
		    sizeof(gpiocells)) < 0) {
			device_printf(consumer,
			    "gpio does not have the #gpio-cells property.\n");
			goto fail;
		}
		/* Return the device reference for the GPIO controller. */
		(*pins)[j].dev = OF_device_from_xref(gpios[i]);
		if ((*pins)[j].dev == NULL) {
			device_printf(consumer,
			    "no device registered for the gpio controller.\n");
			goto fail;
		}
		/*
		 * If the gpiobus softc is NULL we use the GPIO_GET_BUS() to
		 * retrieve it.  The GPIO_GET_BUS() method is only valid after
		 * the child is probed and attached.
		 */
		if (bussc == NULL) {
			if (GPIO_GET_BUS((*pins)[j].dev) == NULL) {
				device_printf(consumer,
				    "no gpiobus reference for %s.\n",
				    device_get_nameunit((*pins)[j].dev));
				goto fail;
			}
			bussc = device_get_softc(GPIO_GET_BUS((*pins)[j].dev));
		}
		/* Get the GPIO pin number and flags. */
		if (gpio_map_gpios((*pins)[j].dev, cnode, gpio, gpiocells,
		    &gpios[i + 1], &(*pins)[j].pin, &(*pins)[j].flags) != 0) {
			device_printf(consumer,
			    "cannot map the gpios specifier.\n");
			goto fail;
		}
		/* Reserve the GPIO pin. */
		if (gpiobus_acquire_pin(bussc->sc_busdev, (*pins)[j].pin) != 0)
			goto fail;
		j++;
		i += gpiocells + 1;
	}
	OF_prop_free(gpios);

	return (npins);

fail:
	OF_prop_free(gpios);
	free(*pins, M_DEVBUF);
	return (-1);
}