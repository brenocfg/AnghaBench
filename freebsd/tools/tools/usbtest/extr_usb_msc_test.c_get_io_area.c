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
struct usb_msc_params {int io_area; } ;

/* Variables and functions */
#define  USB_MSC_IO_AREA_16MB 131 
#define  USB_MSC_IO_AREA_1MB 130 
#define  USB_MSC_IO_AREA_256MB 129 
#define  USB_MSC_IO_AREA_COMPLETE 128 

__attribute__((used)) static const char *
get_io_area(const struct usb_msc_params *p)
{
	;				/* indent fix */
	switch (p->io_area) {
	case USB_MSC_IO_AREA_COMPLETE:
		return ("Complete Disk");
	case USB_MSC_IO_AREA_1MB:
		return ("First MegaByte");
	case USB_MSC_IO_AREA_16MB:
		return ("First 16 MegaBytes");
	case USB_MSC_IO_AREA_256MB:
		return ("First 256 MegaBytes");
	default:
		return ("Unknown");
	}
}