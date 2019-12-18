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
struct acpi_toshiba_softc {int /*<<< orphan*/  dev; } ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_GET ; 
 int /*<<< orphan*/  HCI_REG_SYSTEM_EVENT ; 
 int /*<<< orphan*/  acpi_UserNotify (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ hci_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_key_action (struct acpi_toshiba_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  toshiba ; 

__attribute__((used)) static void
acpi_toshiba_notify(ACPI_HANDLE h, UINT32 notify, void *context)
{
	struct		acpi_toshiba_softc *sc;
	UINT32		key;

	sc = (struct acpi_toshiba_softc *)context;

	if (notify == 0x80) {
		ACPI_SERIAL_BEGIN(toshiba);
		while (hci_call(h, HCI_GET, HCI_REG_SYSTEM_EVENT, &key) == 0) {
			hci_key_action(sc, h, key);
			acpi_UserNotify("TOSHIBA", h, (uint8_t)key);
		}
		ACPI_SERIAL_END(toshiba);
	} else
		device_printf(sc->dev, "unknown notify: 0x%x\n", notify);
}