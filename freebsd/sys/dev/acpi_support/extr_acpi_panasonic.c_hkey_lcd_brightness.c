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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  HKEY_GET 129 
 int HKEY_REG_LCD_BRIGHTNESS_AC ; 
 int HKEY_REG_LCD_BRIGHTNESS_DC ; 
#define  HKEY_SET 128 
 scalar_t__ POWER_PROFILE_PERFORMANCE ; 
 int /*<<< orphan*/  acpi_panasonic_sinf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_panasonic_sset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hkey_lcd_brightness_max (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hkey_lcd_brightness_min (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panasonic ; 
 scalar_t__ power_profile_get_state () ; 

__attribute__((used)) static int
hkey_lcd_brightness(ACPI_HANDLE h, int op, UINT32 *val)
{
	int reg;
	UINT32 max, min;

	reg = (power_profile_get_state() == POWER_PROFILE_PERFORMANCE) ?
	    HKEY_REG_LCD_BRIGHTNESS_AC : HKEY_REG_LCD_BRIGHTNESS_DC;

	ACPI_SERIAL_ASSERT(panasonic);
	switch (op) {
	case HKEY_SET:
		hkey_lcd_brightness_max(h, HKEY_GET, &max);
		hkey_lcd_brightness_min(h, HKEY_GET, &min);
		if (*val < min || *val > max)
			return (EINVAL);
		acpi_panasonic_sset(h, reg, *val);
		break;
	case HKEY_GET:
		*val = acpi_panasonic_sinf(h, reg);
		break;
	}

	return (0);
}