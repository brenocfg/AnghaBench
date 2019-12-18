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
 int /*<<< orphan*/  rx1950_bl_power (int) ; 
 int /*<<< orphan*/  rx1950_lcd_power (int) ; 

__attribute__((used)) static int rx1950_backlight_notify(struct device *dev, int brightness)
{
	if (!brightness) {
		rx1950_bl_power(0);
		rx1950_lcd_power(0);
	} else {
		rx1950_lcd_power(1);
		rx1950_bl_power(1);
	}
	return brightness;
}