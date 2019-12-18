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
struct acpi_toshiba_softc {int /*<<< orphan*/  video_handle; } ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
#define  FN_ESC_RELEASE 132 
#define  FN_F5_RELEASE 131 
#define  FN_F6_RELEASE 130 
#define  FN_F7_RELEASE 129 
#define  FN_F8_RELEASE 128 
 int /*<<< orphan*/  HCI_GET ; 
 int /*<<< orphan*/  HCI_SET ; 
 int /*<<< orphan*/  hci_force_fan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_lcd_backlight (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_lcd_brightness (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_video_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  toshiba ; 

__attribute__((used)) static void
hci_key_action(struct acpi_toshiba_softc *sc, ACPI_HANDLE h, UINT32 key)
{
	UINT32		arg;

	ACPI_SERIAL_ASSERT(toshiba);
	switch (key) {
	case FN_F6_RELEASE:
		/* Decrease LCD brightness. */
		hci_lcd_brightness(h, HCI_GET, &arg);
		if (arg-- == 0)
			arg = 0;
		else
			hci_lcd_brightness(h, HCI_SET, &arg);
		break;
	case FN_F7_RELEASE:
		/* Increase LCD brightness. */
		hci_lcd_brightness(h, HCI_GET, &arg);
		if (arg++ == 7)
			arg = 7;
		else
			hci_lcd_brightness(h, HCI_SET, &arg);
		break;
	case FN_F5_RELEASE:
		/* Cycle through video outputs. */
		hci_video_output(h, HCI_GET, &arg);
		arg = (arg + 1) % 7;
		hci_video_output(sc->video_handle, HCI_SET, &arg);
		break;
	case FN_F8_RELEASE:
		/* Toggle LCD backlight. */
		hci_lcd_backlight(h, HCI_GET, &arg);
		arg = (arg != 0) ? 0 : 1;
		hci_lcd_backlight(h, HCI_SET, &arg);
		break;
	case FN_ESC_RELEASE:
		/* Toggle forcing fan on. */
		hci_force_fan(h, HCI_GET, &arg);
		arg = (arg != 0) ? 0 : 1;
		hci_force_fan(h, HCI_SET, &arg);
		break;
	}
}