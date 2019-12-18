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
 int /*<<< orphan*/  show_device_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_host_select (int /*<<< orphan*/ ) ; 
 int usb_ts_show_menu (int,char*,char*) ; 

__attribute__((used)) static void
show_mode_select(uint8_t level)
{
	uint8_t retval;

	while (1) {

		retval = usb_ts_show_menu(level, "Select Computer Mode",
		    "1) This computer is Running the Device Side\n"
		    "2) This computer is Running the Host Side\n"
		    "x) Return to previous menu\n");

		switch (retval) {
		case 0:
			break;
		case 1:
			show_device_select(level + 1);
			break;
		case 2:
			show_host_select(level + 1);
			break;
		default:
			return;
		}
	}
}