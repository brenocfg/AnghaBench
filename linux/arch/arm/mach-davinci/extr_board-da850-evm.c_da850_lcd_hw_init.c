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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  da850_lcd_backlight_info ; 
 int /*<<< orphan*/  da850_lcd_gpio_lookups ; 
 int /*<<< orphan*/  da850_lcd_supply_device ; 
 int /*<<< orphan*/  gpiod_add_lookup_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_device_register (int /*<<< orphan*/ *) ; 
 struct platform_device* platform_device_register_full (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int da850_lcd_hw_init(void)
{
	struct platform_device *backlight;
	int status;

	gpiod_add_lookup_tables(da850_lcd_gpio_lookups,
				ARRAY_SIZE(da850_lcd_gpio_lookups));

	backlight = platform_device_register_full(&da850_lcd_backlight_info);
	if (IS_ERR(backlight))
		return PTR_ERR(backlight);

	status = platform_device_register(&da850_lcd_supply_device);
	if (status)
		return status;

	return 0;
}