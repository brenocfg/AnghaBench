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
struct fcu_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
struct fcu_fan {scalar_t__ type; int id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ FCU_FAN_RPM ; 
 int FCU_RPM_ACTIVE ; 
 int FCU_RPM_AVAILABLE ; 
 int FCU_RPM_FAIL ; 
 int FCU_RPM_READ (int) ; 
 struct fcu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ fcu_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int fcu_rpm_shift ; 

__attribute__((used)) static int
fcu_fan_get_rpm(struct fcu_fan *fan)
{
	uint8_t reg;
	struct fcu_softc *sc;
	uint8_t buff[2] = { 0, 0 };
	uint8_t active = 0, avail = 0, fail = 0;
	int rpm;

	sc = device_get_softc(fan->dev);

	if (fan->type == FCU_FAN_RPM) {
		/* Check if the fan is available. */
		reg = FCU_RPM_AVAILABLE;
		if (fcu_read_1(sc->sc_dev, sc->sc_addr, reg, &avail) < 0)
			return (-1);
		if ((avail & (1 << fan->id)) == 0) {
			device_printf(fan->dev,
			    "RPM Fan not available ID: %d\n", fan->id);
			return (-1);
		}
		/* Check if we have a failed fan. */
		reg = FCU_RPM_FAIL;
		if (fcu_read_1(sc->sc_dev, sc->sc_addr, reg, &fail) < 0)
			return (-1);
		if ((fail & (1 << fan->id)) != 0) {
			device_printf(fan->dev,
			    "RPM Fan failed ID: %d\n", fan->id);
			return (-1);
		}
		/* Check if fan is active. */
		reg = FCU_RPM_ACTIVE;
		if (fcu_read_1(sc->sc_dev, sc->sc_addr, reg, &active) < 0)
			return (-1);
		if ((active & (1 << fan->id)) == 0) {
			device_printf(fan->dev, "RPM Fan not active ID: %d\n",
				      fan->id);
			return (-1);
		}
		reg = FCU_RPM_READ(fan->id);

	} else {
		device_printf(fan->dev, "Unknown fan type: %d\n", fan->type);
		return (-1);
	}

	/* It seems that we can read the fans rpm. */
	if (fcu_read_1(sc->sc_dev, sc->sc_addr, reg, buff) < 0)
		return (-1);

	rpm = (buff[0] << (8 - fcu_rpm_shift)) | buff[1] >> fcu_rpm_shift;

	return (rpm);
}