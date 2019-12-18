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
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_GET ; 
 int /*<<< orphan*/  HKEY_SET ; 
 int /*<<< orphan*/  hkey_lcd_brightness (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panasonic ; 

__attribute__((used)) static void
acpi_panasonic_power_profile(void *arg)
{
	ACPI_HANDLE handle;
	UINT32 brightness;

	handle = (ACPI_HANDLE)arg;

	/* Reset current brightness according to new power state. */
	ACPI_SERIAL_BEGIN(panasonic);
	hkey_lcd_brightness(handle, HKEY_GET, &brightness);
	hkey_lcd_brightness(handle, HKEY_SET, &brightness);
	ACPI_SERIAL_END(panasonic);
}