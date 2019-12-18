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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  show_device_audio_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_device_ethernet_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_device_generic_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_device_keyboard_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_device_modem_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_device_mouse_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_device_msc_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_device_mtp_select (int /*<<< orphan*/ ) ; 
 int usb_ts_show_menu (int,char*,char*) ; 

__attribute__((used)) static void
show_device_select(uint8_t level)
{
	uint8_t retval;

	while (1) {

		retval = usb_ts_show_menu(level, "Select Device Mode Test Group",
		    "1) Audio (UAUDIO)\n"
		    "2) Mass Storage (MSC)\n"
		    "3) Ethernet (CDCE)\n"
		    "4) Keyboard Input Device (UKBD)\n"
		    "5) Mouse Input Device (UMS)\n"
		    "6) Message Transfer Protocol (MTP)\n"
		    "7) Modem (CDC)\n"
		    "8) Generic Endpoint Loopback (GENERIC)\n"
		    "x) Return to previous menu\n");

		switch (retval) {
		case 0:
			break;
		case 1:
			show_device_audio_select(level + 1);
			break;
		case 2:
			show_device_msc_select(level + 1);
			break;
		case 3:
			show_device_ethernet_select(level + 1);
			break;
		case 4:
			show_device_keyboard_select(level + 1);
			break;
		case 5:
			show_device_mouse_select(level + 1);
			break;
		case 6:
			show_device_mtp_select(level + 1);
			break;
		case 7:
			show_device_modem_select(level + 1);
			break;
		case 8:
			show_device_generic_select(level + 1);
			break;
		default:
			return;
		}
	}
}