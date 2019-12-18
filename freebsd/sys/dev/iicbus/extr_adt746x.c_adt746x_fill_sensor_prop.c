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
struct adt746x_softc {TYPE_1__* sc_sensors; } ;
typedef  int /*<<< orphan*/  sensid ;
typedef  int /*<<< orphan*/  sens_type ;
typedef  int /*<<< orphan*/  reg ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int* name; int zone; int (* read ) (struct pmac_therm*) ;void* max_temp; void* target_temp; } ;
struct TYPE_3__ {scalar_t__ type; int reg; int id; TYPE_2__ therm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ADT746X_SENSOR_SPEED ; 
 scalar_t__ ADT746X_SENSOR_TEMP ; 
 scalar_t__ ADT746X_SENSOR_VOLT ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop (scalar_t__,char*,...) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 void* ZERO_C_TO_K ; 
 scalar_t__ adt746x_sensor_read ; 
 struct adt746x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_thermal_sensor_register (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
adt746x_fill_sensor_prop(device_t dev)
{
	phandle_t child, node;
	struct adt746x_softc *sc;
	char sens_type[32];
	int i = 0, reg, sensid;

	sc = device_get_softc(dev);

	child = ofw_bus_get_node(dev);

	/* Fill in the sensor properties for each child. */
	for (node = OF_child(child); node != 0; node = OF_peer(node)) {
		if (OF_getprop(node, "sensor-id", &sensid, sizeof(sensid)) == -1)
		    continue;
		OF_getprop(node, "location", sc->sc_sensors[i].therm.name, 32);
		OF_getprop(node, "device_type", sens_type, sizeof(sens_type));
		if (strcmp(sens_type, "temperature") == 0)
			sc->sc_sensors[i].type = ADT746X_SENSOR_TEMP;
		else if (strcmp(sens_type, "voltage") == 0)
			sc->sc_sensors[i].type = ADT746X_SENSOR_VOLT;
		else
			sc->sc_sensors[i].type = ADT746X_SENSOR_SPEED;
		OF_getprop(node, "reg", &reg, sizeof(reg));
		OF_getprop(node, "sensor-id", &sensid,
			sizeof(sensid));
		/* This is the i2c register of the sensor.  */
		sc->sc_sensors[i].reg = reg;
		sc->sc_sensors[i].id = sensid;
		OF_getprop(node, "zone", &sc->sc_sensors[i].therm.zone,
			sizeof(sc->sc_sensors[i].therm.zone));
		sc->sc_sensors[i].dev = dev;
		sc->sc_sensors[i].therm.read =
		    (int (*)(struct pmac_therm *))adt746x_sensor_read;
		if (sc->sc_sensors[i].type == ADT746X_SENSOR_TEMP) {
		    /* Make up some ranges */
		    sc->sc_sensors[i].therm.target_temp = 500 + ZERO_C_TO_K;
		    sc->sc_sensors[i].therm.max_temp = 800 + ZERO_C_TO_K;

		    pmac_thermal_sensor_register(&sc->sc_sensors[i].therm);
		}
		i++;
	}

	return (i);
}