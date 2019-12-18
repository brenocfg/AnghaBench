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
typedef  int /*<<< orphan*/  uint32_t ;
struct bhnd_pmu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bhnd_pmu_regulator ;

/* Variables and functions */
#define  BHND_REGULATOR_PAREF_LDO 128 
 int /*<<< orphan*/  BPMU_LOCK (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BPMU_UNLOCK (struct bhnd_pmu_softc*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SET_LDO_VOLTAGE_PAREF ; 
 int /*<<< orphan*/  UINT8_MAX ; 
 int bhnd_pmu_set_ldo_voltage (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_pmu_set_voltage_raw_method(device_t dev, bhnd_pmu_regulator regulator,
    uint32_t value)
{
	struct bhnd_pmu_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	switch (regulator) {
	case BHND_REGULATOR_PAREF_LDO:
		if (value > UINT8_MAX)
			return (EINVAL);
	
		BPMU_LOCK(sc);
		error = bhnd_pmu_set_ldo_voltage(sc, SET_LDO_VOLTAGE_PAREF,
		    value);
		BPMU_UNLOCK(sc);

		return (error);

	default:
		return (ENODEV);
	}
}