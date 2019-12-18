#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct fcu_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_rpm; int /*<<< orphan*/  min_rpm; } ;
struct fcu_fan {scalar_t__ type; int setpoint; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; TYPE_1__ fan; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ FCU_FAN_PWM ; 
 int FCU_PWM_SGET (int /*<<< orphan*/ ) ; 
 struct fcu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ fcu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fcu_fan_set_pwm(struct fcu_fan *fan, int pwm)
{
	uint8_t reg;
	struct fcu_softc *sc;
	uint8_t buf[2];

	sc = device_get_softc(fan->dev);

	/* Clamp to allowed range */
	pwm = max(fan->fan.min_rpm, pwm);
	pwm = min(fan->fan.max_rpm, pwm);

	if (fan->type == FCU_FAN_PWM) {
		reg = FCU_PWM_SGET(fan->id);
		if (pwm > 100)
			pwm = 100;
		if (pwm < 30)
			pwm = 30;
		fan->setpoint = pwm;
	} else {
		device_printf(fan->dev, "Unknown fan type: %d\n", fan->type);
		return (EIO);
	}

	buf[0] = (pwm * 2550) / 1000;

	if (fcu_write(sc->sc_dev, sc->sc_addr, reg, buf, 1) < 0)
		return (EIO);
	return (0);
}