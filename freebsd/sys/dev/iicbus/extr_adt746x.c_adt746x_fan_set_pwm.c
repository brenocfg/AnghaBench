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
struct adt746x_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_rpm; int /*<<< orphan*/  min_rpm; } ;
struct adt746x_fan {int pwm_reg; int conf_reg; int setpoint; TYPE_1__ fan; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADT746X_MANUAL_MASK ; 
 int /*<<< orphan*/  adt746x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  adt746x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 struct adt746x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
adt746x_fan_set_pwm(struct adt746x_fan *fan, int pwm)
{
	uint8_t reg = 0, manual, mode = 0;
	struct adt746x_softc *sc;
	uint8_t buf;

	sc = device_get_softc(fan->dev);

	/* Clamp to allowed range */
	pwm = max(fan->fan.min_rpm, pwm);
	pwm = min(fan->fan.max_rpm, pwm);

	reg = fan->pwm_reg;
	mode = fan->conf_reg;

	/* From the 7460 datasheet:
	   PWM dutycycle can be programmed from 0% (0x00) to 100% (0xFF)
	   in steps of 0.39% (256 steps).
	 */
	buf = (pwm * 100 / 39) - (pwm ? 1 : 0);
	fan->setpoint = buf;

	/* Manual mode.  */
	adt746x_read(sc->sc_dev, sc->sc_addr, mode, &manual);
	manual |= ADT746X_MANUAL_MASK;
	adt746x_write(sc->sc_dev, sc->sc_addr, mode, &manual);

	/* Write speed.  */
	adt746x_write(sc->sc_dev, sc->sc_addr, reg, &buf);

	return (0);
}