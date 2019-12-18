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
typedef  int uint16_t ;
struct am335x_ecap_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECAP_CAP3 ; 
 int /*<<< orphan*/  ECAP_CAP4 ; 
 int /*<<< orphan*/  ECAP_ECCTL2 ; 
 int ECAP_READ2 (struct am335x_ecap_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECAP_TSCTR ; 
 int /*<<< orphan*/  ECAP_WRITE2 (struct am335x_ecap_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ECAP_WRITE4 (struct am335x_ecap_softc*,int /*<<< orphan*/ ,int) ; 
 int ECCTL2_MODE_APWM ; 
 int ECCTL2_SYNCO_SEL ; 
 int ECCTL2_TSCTRSTOP_FREERUN ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  PWM_LOCK (struct am335x_ecap_softc*) ; 
 int /*<<< orphan*/  PWM_UNLOCK (struct am335x_ecap_softc*) ; 
 int /*<<< orphan*/  am335x_ecap_devclass ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 struct am335x_ecap_softc* device_get_softc (int /*<<< orphan*/ *) ; 

int
am335x_pwm_config_ecap(int unit, int period, int duty)
{
	device_t dev;
	struct am335x_ecap_softc *sc;
	uint16_t reg;

	dev = devclass_get_device(am335x_ecap_devclass, unit);
	if (dev == NULL)
		return (ENXIO);

	if (duty > period)
		return (EINVAL);

	if (period == 0)
		return (EINVAL);

	sc = device_get_softc(dev);
	PWM_LOCK(sc);

	reg = ECAP_READ2(sc, ECAP_ECCTL2);
	reg |= ECCTL2_MODE_APWM | ECCTL2_TSCTRSTOP_FREERUN | ECCTL2_SYNCO_SEL;
	ECAP_WRITE2(sc, ECAP_ECCTL2, reg);

	/* CAP3 in APWM mode is APRD shadow register */
	ECAP_WRITE4(sc, ECAP_CAP3, period - 1);

	/* CAP4 in APWM mode is ACMP shadow register */
	ECAP_WRITE4(sc, ECAP_CAP4, duty);
	/* Restart counter */
	ECAP_WRITE4(sc, ECAP_TSCTR, 0);

	PWM_UNLOCK(sc);

	return (0);
}