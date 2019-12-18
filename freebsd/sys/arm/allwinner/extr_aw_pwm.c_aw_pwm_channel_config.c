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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct aw_pwm_softc {int period; int duty; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AW_PWM_CTRL ; 
 int AW_PWM_CTRL_PERIOD_BUSY ; 
 int AW_PWM_CTRL_PRESCALE_MASK ; 
 int AW_PWM_MAX_FREQ ; 
 int /*<<< orphan*/  AW_PWM_PERIOD ; 
 int AW_PWM_PERIOD_ACTIVE_SHIFT ; 
 int AW_PWM_PERIOD_TOTAL_MASK ; 
 int AW_PWM_PERIOD_TOTAL_SHIFT ; 
 int AW_PWM_READ (struct aw_pwm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_PWM_WRITE (struct aw_pwm_softc*,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int NS_PER_SEC ; 
 int* aw_pwm_clk_prescaler ; 
 struct aw_pwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nitems (int*) ; 

__attribute__((used)) static int
aw_pwm_channel_config(device_t dev, u_int channel, u_int period, u_int duty)
{
	struct aw_pwm_softc *sc;
	uint64_t period_freq, duty_freq;
	uint64_t clk_rate, div;
	uint32_t reg;
	int prescaler;
	int i;

	sc = device_get_softc(dev);

	period_freq = NS_PER_SEC / period;
	if (period_freq > AW_PWM_MAX_FREQ)
		return (EINVAL);
	duty_freq = NS_PER_SEC / duty;
	if (duty_freq < period_freq) {
		device_printf(sc->dev, "duty < period\n");
		return (EINVAL);
	}

	/* First test without prescaler */
	clk_rate = AW_PWM_MAX_FREQ;
	prescaler = AW_PWM_CTRL_PRESCALE_MASK;
	div = AW_PWM_MAX_FREQ / period_freq;
	if ((div - 1) > AW_PWM_PERIOD_TOTAL_MASK) {
		/* Test all prescaler */
		for (i = 0; i < nitems(aw_pwm_clk_prescaler); i++) {
			if (aw_pwm_clk_prescaler[i] == 0)
				continue;
			div = (AW_PWM_MAX_FREQ * aw_pwm_clk_prescaler[i]) / period_freq;
			if ((div - 1) < AW_PWM_PERIOD_TOTAL_MASK ) {
				prescaler = i;
				clk_rate = AW_PWM_MAX_FREQ / aw_pwm_clk_prescaler[i];
				break;
			}
		}
		if (prescaler == AW_PWM_CTRL_PRESCALE_MASK)
			return (EINVAL);
	}

	reg = AW_PWM_READ(sc, AW_PWM_CTRL);
	if (reg & AW_PWM_CTRL_PERIOD_BUSY) {
		device_printf(sc->dev, "pwm busy\n");
		return (EBUSY);
	}

	/* Write the prescalar */
	reg &= ~AW_PWM_CTRL_PRESCALE_MASK;
	reg |= prescaler;
	AW_PWM_WRITE(sc, AW_PWM_CTRL, reg);

	/* Write the total/active cycles */
	reg = ((clk_rate / period_freq) << AW_PWM_PERIOD_TOTAL_SHIFT) |
	  ((clk_rate / duty_freq) << AW_PWM_PERIOD_ACTIVE_SHIFT);
	AW_PWM_WRITE(sc, AW_PWM_PERIOD, reg);

	sc->period = period;
	sc->duty = duty;

	return (0);
}