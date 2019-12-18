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
typedef  char u_int ;
typedef  int /*<<< orphan*/  type ;
struct ad7417_softc {TYPE_1__* sc_sensors; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  location ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {char zone; int (* read ) (struct pmac_therm*) ;void* max_temp; void* target_temp; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ type; char id; TYPE_2__ therm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ADC7417_ADC_SENSOR ; 
 scalar_t__ ADC7417_TEMP_SENSOR ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 void* ZERO_C_TO_K ; 
 scalar_t__ ad7417_diode_read ; 
 scalar_t__ ad7417_sensor_read ; 
 struct ad7417_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_thermal_sensor_register (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ad7417_fill_sensor_prop(device_t dev)
{
	phandle_t child;
	struct ad7417_softc *sc;
	u_int id[10];
	char location[96];
	char type[32];
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

	/* Fill the sensor type property. */
	len = 0;
	i = 0;
	prev_len = 0;
	prop_len = OF_getprop(child, "hwsensor-type", type, sizeof(type));
	while (len < prop_len) {
		if (strcmp(type + len, "temperature") == 0)
			sc->sc_sensors[i].type = ADC7417_TEMP_SENSOR;
		else
			sc->sc_sensors[i].type = ADC7417_ADC_SENSOR;
		prev_len = strlen(type + len) + 1;
		len += prev_len;
		i++;
	}

	/* Fill the sensor id property. Taken from OF. */
	prop_len = OF_getprop(child, "hwsensor-id", id, sizeof(id));
	for (j = 0; j < i; j++)
		sc->sc_sensors[j].id = id[j];

	/* Fill the sensor zone property. Taken from OF. */
	prop_len = OF_getprop(child, "hwsensor-zone", id, sizeof(id));
	for (j = 0; j < i; j++)
		sc->sc_sensors[j].therm.zone = id[j];

	/* Finish setting up sensor properties */
	for (j = 0; j < i; j++) {
		sc->sc_sensors[j].dev = dev;
	
		/* HACK: Apple wired a random diode to the ADC line */
		if (strstr(sc->sc_sensors[j].therm.name, "DIODE TEMP")
		    != NULL) {
			sc->sc_sensors[j].type = ADC7417_TEMP_SENSOR;
			sc->sc_sensors[j].therm.read =
			    (int (*)(struct pmac_therm *))(ad7417_diode_read);
		} else {
			sc->sc_sensors[j].therm.read =
			    (int (*)(struct pmac_therm *))(ad7417_sensor_read);
		}
			
		if (sc->sc_sensors[j].type != ADC7417_TEMP_SENSOR)
			continue;

		/* Make up some ranges */
		sc->sc_sensors[j].therm.target_temp = 500 + ZERO_C_TO_K;
		sc->sc_sensors[j].therm.max_temp = 900 + ZERO_C_TO_K;
		
		pmac_thermal_sensor_register(&sc->sc_sensors[j].therm);
	}

	return (i);
}