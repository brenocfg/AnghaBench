#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct max6690_softc {TYPE_2__* sc_sensors; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  location ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int zone; int (* read ) (struct pmac_therm*) ;void* max_temp; void* target_temp; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int id; TYPE_1__ therm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int OF_getprop (int /*<<< orphan*/ ,char*,...) ; 
 void* ZERO_C_TO_K ; 
 struct max6690_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ max6690_sensor_read ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
max6690_fill_sensor_prop(device_t dev)
{
	phandle_t child;
	struct max6690_softc *sc;
	u_int id[8];
	char location[96];
	int i = 0, j, len = 0, prop_len, prev_len = 0;

	sc = device_get_softc(dev);

	child = ofw_bus_get_node(dev);

	/* Fill the sensor location property. */
	prop_len = OF_getprop(child, "hwsensor-location", location,
			      sizeof(location));
	while (len < prop_len) {
		if (sc->sc_sensors != NULL)
			strcpy(sc->sc_sensors[i].therm.name, location + len);
		prev_len = strlen(location + len) + 1;
		len += prev_len;
		i++;
	}
	if (sc->sc_sensors == NULL)
		return (i);

	/* Fill the sensor id property. */
	prop_len = OF_getprop(child, "hwsensor-id", id, sizeof(id));
	for (j = 0; j < i; j++)
		sc->sc_sensors[j].id = (id[j] & 0xf);

	/* Fill the sensor zone property. */
	prop_len = OF_getprop(child, "hwsensor-zone", id, sizeof(id));
	for (j = 0; j < i; j++)
		sc->sc_sensors[j].therm.zone = id[j];

	/* Set up remaining sensor properties */
	for (j = 0; j < i; j++) {
		sc->sc_sensors[j].dev = dev;

		sc->sc_sensors[j].therm.target_temp = 400 + ZERO_C_TO_K;
		sc->sc_sensors[j].therm.max_temp = 800 + ZERO_C_TO_K;

		sc->sc_sensors[j].therm.read =
		    (int (*)(struct pmac_therm *))(max6690_sensor_read);
	}

	return (i);
}