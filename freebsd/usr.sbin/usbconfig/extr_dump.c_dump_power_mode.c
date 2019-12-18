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
#define  LIBUSB20_POWER_OFF 132 
#define  LIBUSB20_POWER_ON 131 
#define  LIBUSB20_POWER_RESUME 130 
#define  LIBUSB20_POWER_SAVE 129 
#define  LIBUSB20_POWER_SUSPEND 128 

const char *
dump_power_mode(uint8_t value)
{
	;				/* style fix */
	switch (value) {
	case LIBUSB20_POWER_OFF:
		return ("OFF");
	case LIBUSB20_POWER_ON:
		return ("ON");
	case LIBUSB20_POWER_SAVE:
		return ("SAVE");
	case LIBUSB20_POWER_SUSPEND:
		return ("SUSPEND");
	case LIBUSB20_POWER_RESUME:
		return ("RESUME");
	default:
		return ("UNKNOWN");
	}
}