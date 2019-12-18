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
 int EPERM ; 
#define  HKEY_GET 129 
 int HKEY_REG_LCD_BRIGHTNESS_MIN_AC ; 
 int HKEY_REG_LCD_BRIGHTNESS_MIN_DC ; 
#define  HKEY_SET 128 
 scalar_t__ POWER_PROFILE_PERFORMANCE ; 
 int /*<<< orphan*/  acpi_panasonic_sinf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panasonic ; 
 scalar_t__ power_profile_get_state () ; 

__attribute__((used)) static int
hkey_lcd_brightness_min(ACPI_HANDLE h, int op, UINT32 *val)
{
	int reg;

	ACPI_SERIAL_ASSERT(panasonic);
	reg = (power_profile_get_state() == POWER_PROFILE_PERFORMANCE) ?
	    HKEY_REG_LCD_BRIGHTNESS_MIN_AC : HKEY_REG_LCD_BRIGHTNESS_MIN_DC;

	switch (op) {
	case HKEY_SET:
		return (EPERM);
		break;
	case HKEY_GET:
		*val = acpi_panasonic_sinf(h, reg);
		break;
	}

	return (0);
}