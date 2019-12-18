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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C2410_GPB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lcd_pwm ; 
 int /*<<< orphan*/  pwm_apply_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_request (int,char*) ; 
 int /*<<< orphan*/  rx1950_bl_power (int) ; 
 int /*<<< orphan*/  rx1950_lcd_power (int) ; 

__attribute__((used)) static int rx1950_backlight_init(struct device *dev)
{
	WARN_ON(gpio_request(S3C2410_GPB(0), "Backlight"));
	lcd_pwm = pwm_request(1, "RX1950 LCD");
	if (IS_ERR(lcd_pwm)) {
		dev_err(dev, "Unable to request PWM for LCD power!\n");
		return PTR_ERR(lcd_pwm);
	}

	/*
	 * FIXME: pwm_apply_args() should be removed when switching to
	 * the atomic PWM API.
	 */
	pwm_apply_args(lcd_pwm);

	rx1950_lcd_power(1);
	rx1950_bl_power(1);

	return 0;
}