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
struct fb_var_screeninfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGPIO_MAGICIAN_LCD_POWER ; 
 int /*<<< orphan*/  GPIO104_MAGICIAN_LCD_VOFF_EN ; 
 int /*<<< orphan*/  GPIO105_MAGICIAN_LCD_VON_EN ; 
 int /*<<< orphan*/  GPIO106_MAGICIAN_LCD_DCDC_NRESET ; 
 int /*<<< orphan*/  GPIO75_MAGICIAN_SAMSUNG_POWER ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int system_rev ; 

__attribute__((used)) static void samsung_lcd_power(int on, struct fb_var_screeninfo *si)
{
	pr_debug("Samsung LCD power: %s\n", on ? "on" : "off");

	if (on) {
		if (system_rev < 3)
			gpio_set_value(GPIO75_MAGICIAN_SAMSUNG_POWER, 1);
		else
			gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 1);
		mdelay(6);
		gpio_set_value(GPIO106_MAGICIAN_LCD_DCDC_NRESET, 1);
		mdelay(6);	/* Avdd -> Voff >5ms */
		gpio_set_value(GPIO104_MAGICIAN_LCD_VOFF_EN, 1);
		mdelay(16);	/* Voff -> Von >(5+10)ms */
		gpio_set_value(GPIO105_MAGICIAN_LCD_VON_EN, 1);
	} else {
		gpio_set_value(GPIO105_MAGICIAN_LCD_VON_EN, 0);
		mdelay(16);
		gpio_set_value(GPIO104_MAGICIAN_LCD_VOFF_EN, 0);
		mdelay(6);
		gpio_set_value(GPIO106_MAGICIAN_LCD_DCDC_NRESET, 0);
		mdelay(6);
		if (system_rev < 3)
			gpio_set_value(GPIO75_MAGICIAN_SAMSUNG_POWER, 0);
		else
			gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 0);
	}
}