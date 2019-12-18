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
struct usb_msc_params {int io_mode; } ;

/* Variables and functions */
#define  USB_MSC_IO_MODE_READ_ONLY 131 
#define  USB_MSC_IO_MODE_READ_WRITE 130 
#define  USB_MSC_IO_MODE_WRITE_ONCE_READ_ONLY 129 
#define  USB_MSC_IO_MODE_WRITE_ONLY 128 

__attribute__((used)) static const char *
get_io_mode(const struct usb_msc_params *p)
{
	;				/* indent fix */
	switch (p->io_mode) {
	case USB_MSC_IO_MODE_READ_ONLY:
		return ("Read Only");
	case USB_MSC_IO_MODE_WRITE_ONCE_READ_ONLY:
		return ("Write Once, Read Only");
	case USB_MSC_IO_MODE_WRITE_ONLY:
		return ("Write Only");
	case USB_MSC_IO_MODE_READ_WRITE:
		return ("Read and Write");
	default:
		return ("Unknown");
	}
}