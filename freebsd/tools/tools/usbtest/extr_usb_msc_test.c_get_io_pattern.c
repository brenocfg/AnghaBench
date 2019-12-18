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
struct usb_msc_params {int io_pattern; } ;

/* Variables and functions */
#define  USB_MSC_IO_PATTERN_FIXED 130 
#define  USB_MSC_IO_PATTERN_PRESERVE 129 
#define  USB_MSC_IO_PATTERN_RANDOM 128 

__attribute__((used)) static const char *
get_io_pattern(const struct usb_msc_params *p)
{
	;				/* indent fix */
	switch (p->io_pattern) {
	case USB_MSC_IO_PATTERN_FIXED:
		return ("Fixed");
	case USB_MSC_IO_PATTERN_RANDOM:
		return ("Random");
	case USB_MSC_IO_PATTERN_PRESERVE:
		return ("Preserve");
	default:
		return ("Unknown");
	}
}