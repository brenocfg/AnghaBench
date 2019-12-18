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
struct smusat_softc {int sc_last_update; int* sc_cache; } ;
struct smu_sensor {int reg; int type; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SMU_CURRENT_SENSOR 131 
#define  SMU_POWER_SENSOR 130 
#define  SMU_TEMP_SENSOR 129 
#define  SMU_VOLTAGE_SENSOR 128 
 struct smusat_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int smusat_updatecache (int /*<<< orphan*/ ) ; 
 int time_uptime ; 

__attribute__((used)) static int
smusat_sensor_read(struct smu_sensor *sens)
{
	int value, error;
	device_t dev;
	struct smusat_softc *sc;

	dev = sens->dev;
	sc = device_get_softc(dev);
	error = 0;

	if (time_uptime - sc->sc_last_update > 1)
		error = smusat_updatecache(dev);
	if (error)
		return (-error);

	value = (sc->sc_cache[sens->reg*2] << 8) +
	    sc->sc_cache[sens->reg*2 + 1];
	if (value == 0xffff) {
		sc->sc_last_update = 0; /* Result was bad, don't cache */
		return (-EINVAL);
	}

	switch (sens->type) {
	case SMU_TEMP_SENSOR:
		/* 16.16 */
		value <<= 10;
		/* From 16.16 to 0.1 C */
		value = 10*(value >> 16) + ((10*(value & 0xffff)) >> 16) + 2731;
		break;
	case SMU_VOLTAGE_SENSOR:
		/* 16.16 */
		value <<= 4;
		/* Kill the .16 */
		value >>= 16;
		break;
	case SMU_CURRENT_SENSOR:
		/* 16.16 */
		value <<= 8;
		/* Kill the .16 */
		value >>= 16;
		break;
	case SMU_POWER_SENSOR:
		/* Doesn't exist */
		break;
	}

	return (value);
}