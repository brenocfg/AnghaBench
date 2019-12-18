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
struct acpi_softc {int dummy; } ;
struct acpi_panasonic_softc {int /*<<< orphan*/  dev; } ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_GET ; 
 int HKEY_LCD_BRIGHTNESS_DIV ; 
 int /*<<< orphan*/  HKEY_SET ; 
 struct acpi_softc* acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_event_sleep_button_sleep (struct acpi_softc*) ; 
 int /*<<< orphan*/  hkey_lcd_brightness (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hkey_lcd_brightness_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hkey_lcd_brightness_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hkey_sound_mute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  panasonic ; 

__attribute__((used)) static void
acpi_panasonic_hkey_action(struct acpi_panasonic_softc *sc, ACPI_HANDLE h,
    UINT32 key)
{
	struct acpi_softc *acpi_sc;
	int arg, max, min;

	acpi_sc = acpi_device_get_parent_softc(sc->dev);

	ACPI_SERIAL_ASSERT(panasonic);
	switch (key) {
	case 1:
		/* Decrease LCD brightness. */
		hkey_lcd_brightness_max(h, HKEY_GET, &max);
		hkey_lcd_brightness_min(h, HKEY_GET, &min);
		hkey_lcd_brightness(h, HKEY_GET, &arg);
		arg -= max / HKEY_LCD_BRIGHTNESS_DIV;
		if (arg < min)
			arg = min;
		else if (arg > max)
			arg = max;
		hkey_lcd_brightness(h, HKEY_SET, &arg);
		break;
	case 2:
		/* Increase LCD brightness. */
		hkey_lcd_brightness_max(h, HKEY_GET, &max);
		hkey_lcd_brightness_min(h, HKEY_GET, &min);
		hkey_lcd_brightness(h, HKEY_GET, &arg);
		arg += max / HKEY_LCD_BRIGHTNESS_DIV;
		if (arg < min)
			arg = min;
		else if (arg > max)
			arg = max;
		hkey_lcd_brightness(h, HKEY_SET, &arg);
		break;
	case 4:
		/* Toggle sound mute. */
		hkey_sound_mute(h, HKEY_GET, &arg);
		if (arg)
			arg = 0;
		else
			arg = 1;
		hkey_sound_mute(h, HKEY_SET, &arg);
		break;
	case 7:
		/* Suspend. */
		acpi_event_sleep_button_sleep(acpi_sc);
		break;
	}
}