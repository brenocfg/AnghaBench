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
struct usb_msc_params {int io_size; } ;

/* Variables and functions */
#define  USB_MSC_IO_SIZE_FIXED_1024BLK 140 
#define  USB_MSC_IO_SIZE_FIXED_128BLK 139 
#define  USB_MSC_IO_SIZE_FIXED_16BLK 138 
#define  USB_MSC_IO_SIZE_FIXED_1BLK 137 
#define  USB_MSC_IO_SIZE_FIXED_256BLK 136 
#define  USB_MSC_IO_SIZE_FIXED_2BLK 135 
#define  USB_MSC_IO_SIZE_FIXED_32BLK 134 
#define  USB_MSC_IO_SIZE_FIXED_4BLK 133 
#define  USB_MSC_IO_SIZE_FIXED_512BLK 132 
#define  USB_MSC_IO_SIZE_FIXED_64BLK 131 
#define  USB_MSC_IO_SIZE_FIXED_8BLK 130 
#define  USB_MSC_IO_SIZE_INCREASING 129 
#define  USB_MSC_IO_SIZE_RANDOM 128 

__attribute__((used)) static const char *
get_io_size(const struct usb_msc_params *p)
{
	;				/* indent fix */
	switch (p->io_size) {
	case USB_MSC_IO_SIZE_RANDOM:
		return ("Random");
	case USB_MSC_IO_SIZE_INCREASING:
		return ("Increasing");
	case USB_MSC_IO_SIZE_FIXED_1BLK:
		return ("Single block");
	case USB_MSC_IO_SIZE_FIXED_2BLK:
		return ("2 blocks");
	case USB_MSC_IO_SIZE_FIXED_4BLK:
		return ("4 blocks");
	case USB_MSC_IO_SIZE_FIXED_8BLK:
		return ("8 blocks");
	case USB_MSC_IO_SIZE_FIXED_16BLK:
		return ("16 blocks");
	case USB_MSC_IO_SIZE_FIXED_32BLK:
		return ("32 blocks");
	case USB_MSC_IO_SIZE_FIXED_64BLK:
		return ("64 blocks");
	case USB_MSC_IO_SIZE_FIXED_128BLK:
		return ("128 blocks");
	case USB_MSC_IO_SIZE_FIXED_256BLK:
		return ("256 blocks");
	case USB_MSC_IO_SIZE_FIXED_512BLK:
		return ("512 blocks");
	case USB_MSC_IO_SIZE_FIXED_1024BLK:
		return ("1024 blocks");
	default:
		return ("Unknown");
	}
}