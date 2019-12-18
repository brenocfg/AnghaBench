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
typedef  int uint8_t ;
struct pmu_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mutex; } ;
struct pmu_battstate {int state; int charge; int maxcharge; int voltage; int /*<<< orphan*/  current; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_SMART_BATTERY_STATE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int pmu_send (struct pmu_softc*,int /*<<< orphan*/ ,int,int*,int,int*) ; 

__attribute__((used)) static int
pmu_query_battery(struct pmu_softc *sc, int batt, struct pmu_battstate *info)
{
	uint8_t reg;
	uint8_t resp[16];
	int len;

	reg = batt + 1;

	mtx_lock(&sc->sc_mutex);
	len = pmu_send(sc, PMU_SMART_BATTERY_STATE, 1, &reg, 16, resp);
	mtx_unlock(&sc->sc_mutex);

	if (len < 3)
		return (-1);

	/* All PMU battery info replies share a common header:
	 * Byte 1	Payload Format
	 * Byte 2	Battery Flags
	 */

	info->state = resp[2];

	switch (resp[1]) {
	case 3:
	case 4:	
		/*
		 * Formats 3 and 4 appear to be the same:
		 * Byte 3	Charge
		 * Byte 4	Max Charge
		 * Byte 5	Current
		 * Byte 6	Voltage
		 */

		info->charge = resp[3];
		info->maxcharge = resp[4];
		/* Current can be positive or negative */
		info->current = (int8_t)resp[5];
		info->voltage = resp[6];
		break;
	case 5:
		/*
		 * Formats 5 is a wider version of formats 3 and 4
		 * Byte 3-4	Charge
		 * Byte 5-6	Max Charge
		 * Byte 7-8	Current
		 * Byte 9-10	Voltage
		 */

		info->charge = (resp[3] << 8) | resp[4];
		info->maxcharge = (resp[5] << 8) | resp[6];
		/* Current can be positive or negative */
		info->current = (int16_t)((resp[7] << 8) | resp[8]);
		info->voltage = (resp[9] << 8) | resp[10];
		break;
	default:
		device_printf(sc->sc_dev, "Unknown battery info format (%d)!\n",
		    resp[1]);
		return (-1);
	}

	return (0);
}