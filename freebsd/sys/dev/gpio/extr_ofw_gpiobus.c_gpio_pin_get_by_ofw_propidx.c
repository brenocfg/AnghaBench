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
struct gpiobus_pin {int /*<<< orphan*/  pin; int /*<<< orphan*/  flags; int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  struct gpiobus_pin* gpio_pin_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/ * GPIO_GET_BUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (int /*<<< orphan*/ *) ; 
 int gpio_map_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gpiobus_acquire_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gpiobus_pin* malloc (int,int /*<<< orphan*/ ,int) ; 
 int ofw_bus_parse_xref_list_alloc (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **) ; 

int
gpio_pin_get_by_ofw_propidx(device_t consumer, phandle_t cnode,
    char *prop_name, int idx, gpio_pin_t *out_pin)
{
	phandle_t xref;
	pcell_t *cells;
	device_t busdev;
	struct gpiobus_pin pin;
	int ncells, rv;

	KASSERT(consumer != NULL && cnode > 0,
	    ("both consumer and cnode required"));

	rv = ofw_bus_parse_xref_list_alloc(cnode, prop_name, "#gpio-cells",
	    idx, &xref, &ncells, &cells);
	if (rv != 0)
		return (rv);

	/* Translate provider to device. */
	pin.dev = OF_device_from_xref(xref);
	if (pin.dev == NULL) {
		OF_prop_free(cells);
		return (ENODEV);
	}

	/* Test if GPIO bus already exist. */
	busdev = GPIO_GET_BUS(pin.dev);
	if (busdev == NULL) {
		OF_prop_free(cells);
		return (ENODEV);
	}

	/* Map GPIO pin. */
	rv = gpio_map_gpios(pin.dev, cnode, OF_node_from_xref(xref), ncells,
	    cells, &pin.pin, &pin.flags);
	OF_prop_free(cells);
	if (rv != 0)
		return (ENXIO);

	/* Reserve GPIO pin. */
	rv = gpiobus_acquire_pin(busdev, pin.pin);
	if (rv != 0)
		return (EBUSY);

	*out_pin = malloc(sizeof(struct gpiobus_pin), M_DEVBUF,
	    M_WAITOK | M_ZERO);
	**out_pin = pin;
	return (0);
}