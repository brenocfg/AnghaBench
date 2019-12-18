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
struct usb_msc_params {int io_offset; } ;

/* Variables and functions */
#define  USB_MSC_IO_OFF_RANDOM 129 
#define  USB_MSC_IO_OFF_START_OF_DISK 128 

__attribute__((used)) static const char *
get_io_offset(const struct usb_msc_params *p)
{
	;				/* indent fix */
	switch (p->io_offset) {
	case USB_MSC_IO_OFF_START_OF_DISK:
		return ("Start Of Disk");
	case USB_MSC_IO_OFF_RANDOM:
		return ("Random Offset");
	default:
		return ("Unknown");
	}
}