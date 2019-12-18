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
struct usb_msc_params {int io_delay; } ;

/* Variables and functions */
#define  USB_MSC_IO_DELAY_FIXED_100MS 132 
#define  USB_MSC_IO_DELAY_FIXED_10MS 131 
#define  USB_MSC_IO_DELAY_NONE 130 
#define  USB_MSC_IO_DELAY_RANDOM_100MS 129 
#define  USB_MSC_IO_DELAY_RANDOM_10MS 128 

__attribute__((used)) static const char *
get_io_delay(const struct usb_msc_params *p)
{
	;				/* indent fix */
	switch (p->io_delay) {
	case USB_MSC_IO_DELAY_NONE:
		return ("None");
	case USB_MSC_IO_DELAY_RANDOM_10MS:
		return ("Random 10ms");
	case USB_MSC_IO_DELAY_RANDOM_100MS:
		return ("Random 100ms");
	case USB_MSC_IO_DELAY_FIXED_10MS:
		return ("Fixed 10ms");
	case USB_MSC_IO_DELAY_FIXED_100MS:
		return ("Fixed 100ms");
	default:
		return ("Unknown");
	}
}