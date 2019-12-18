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
typedef  int uint32_t ;
struct gpiobus_ivar {int npins; int /*<<< orphan*/  rl; int /*<<< orphan*/ * pins; } ;
struct ofw_gpiobus_devinfo {struct gpiobus_ivar opd_dinfo; int /*<<< orphan*/  pin; int /*<<< orphan*/  opd_obdinfo; } ;
struct gpiobus_softc {int dummy; } ;
struct gpiobus_pin {struct gpiobus_ivar opd_dinfo; int /*<<< orphan*/  pin; int /*<<< orphan*/  opd_obdinfo; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct gpiobus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct ofw_gpiobus_devinfo*) ; 
 int /*<<< orphan*/  free (struct ofw_gpiobus_devinfo*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiobus_alloc_ivars (struct gpiobus_ivar*) ; 
 struct ofw_gpiobus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_intr_to_rl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_gpiobus_destroy_devinfo (int /*<<< orphan*/ ,struct ofw_gpiobus_devinfo*) ; 
 int ofw_gpiobus_parse_gpios_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gpiobus_softc*,struct ofw_gpiobus_devinfo**) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ofw_gpiobus_devinfo *
ofw_gpiobus_setup_devinfo(device_t bus, device_t child, phandle_t node)
{
	int i, npins;
	struct gpiobus_ivar *devi;
	struct gpiobus_pin *pins;
	struct gpiobus_softc *sc;
	struct ofw_gpiobus_devinfo *dinfo;

	sc = device_get_softc(bus);
	dinfo = malloc(sizeof(*dinfo), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (dinfo == NULL)
		return (NULL);
	if (ofw_bus_gen_setup_devinfo(&dinfo->opd_obdinfo, node) != 0) {
		free(dinfo, M_DEVBUF);
		return (NULL);
	}
	/* Parse the gpios property for the child. */
	npins = ofw_gpiobus_parse_gpios_impl(child, node, "gpios", sc, &pins);
	if (npins <= 0) {
		ofw_bus_gen_destroy_devinfo(&dinfo->opd_obdinfo);
		free(dinfo, M_DEVBUF);
		return (NULL);
	}
	/* Initialize the irq resource list. */
	resource_list_init(&dinfo->opd_dinfo.rl);
	/* Allocate the child ivars and copy the parsed pin data. */
	devi = &dinfo->opd_dinfo;
	devi->npins = (uint32_t)npins;
	if (gpiobus_alloc_ivars(devi) != 0) {
		free(pins, M_DEVBUF);
		ofw_gpiobus_destroy_devinfo(bus, dinfo);
		return (NULL);
	}
	for (i = 0; i < devi->npins; i++)
		devi->pins[i] = pins[i].pin;
	free(pins, M_DEVBUF);
	/* Parse the interrupt resources. */
	if (ofw_bus_intr_to_rl(bus, node, &dinfo->opd_dinfo.rl, NULL) != 0) {
		ofw_gpiobus_destroy_devinfo(bus, dinfo);
		return (NULL);
	}
	device_set_ivars(child, dinfo);

	return (dinfo);
}