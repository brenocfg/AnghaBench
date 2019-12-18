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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct aw_pwm_softc {int enabled; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AW_PWM_CTRL ; 
 int AW_PWM_CTRL_EN ; 
 int AW_PWM_CTRL_GATE ; 
 int AW_PWM_READ (struct aw_pwm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_PWM_WRITE (struct aw_pwm_softc*,int /*<<< orphan*/ ,int) ; 
 struct aw_pwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_pwm_channel_enable(device_t dev, u_int channel, bool enable)
{
	struct aw_pwm_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	if (enable && sc->enabled)
		return (0);

	reg = AW_PWM_READ(sc, AW_PWM_CTRL);
	if (enable)
		reg |= AW_PWM_CTRL_GATE | AW_PWM_CTRL_EN;
	else
		reg &= ~(AW_PWM_CTRL_GATE | AW_PWM_CTRL_EN);

	AW_PWM_WRITE(sc, AW_PWM_CTRL, reg);

	sc->enabled = enable;

	return (0);
}