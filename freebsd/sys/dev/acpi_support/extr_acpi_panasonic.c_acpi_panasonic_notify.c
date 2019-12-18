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
typedef  int /*<<< orphan*/  uint8_t ;
struct acpi_panasonic_softc {int /*<<< orphan*/  dev; } ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_UserNotify (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_panasonic_hkey_action (struct acpi_panasonic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_panasonic_hkey_event (struct acpi_panasonic_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  panasonic ; 

__attribute__((used)) static void
acpi_panasonic_notify(ACPI_HANDLE h, UINT32 notify, void *context)
{
	struct acpi_panasonic_softc *sc;
	UINT32 key = 0;

	sc = (struct acpi_panasonic_softc *)context;

	switch (notify) {
	case 0x80:
		ACPI_SERIAL_BEGIN(panasonic);
		if (acpi_panasonic_hkey_event(sc, h, &key) == 0) {
			acpi_panasonic_hkey_action(sc, h, key);
			acpi_UserNotify("Panasonic", h, (uint8_t)key);
		}
		ACPI_SERIAL_END(panasonic);
		break;
	case 0x81:
		if (!bootverbose)
			break;
		/* FALLTHROUGH */
	default:
		device_printf(sc->dev, "unknown notify: %#x\n", notify);
		break;
	}
}