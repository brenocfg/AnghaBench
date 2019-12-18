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
struct adm1030_softc {int sc_pwm; int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 scalar_t__ adm1030_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int adm1030_set(struct adm1030_softc *fan, int pwm)
{
	/* Clamp the PWM to 0-0xF, one nibble. */
	if (pwm > 0xF)
		pwm = 0xF;
	if (pwm < 0)
		pwm = 0;

	if (adm1030_write_byte(fan->sc_dev, fan->sc_addr, 0x22, pwm) < 0)
		return (-1);

	fan->sc_pwm = pwm;
	return (0);
}