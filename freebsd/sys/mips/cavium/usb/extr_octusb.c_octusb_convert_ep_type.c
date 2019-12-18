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
typedef  int /*<<< orphan*/  cvmx_usb_transfer_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_TRANSFER_BULK ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_CONTROL ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_INTERRUPT ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_ISOCHRONOUS ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int UE_XFERTYPE ; 

__attribute__((used)) static cvmx_usb_transfer_t
octusb_convert_ep_type(uint8_t ep_type)
{
	;				/* indent fix */
	switch (ep_type & UE_XFERTYPE) {
	case UE_CONTROL:
		return (CVMX_USB_TRANSFER_CONTROL);
	case UE_INTERRUPT:
		return (CVMX_USB_TRANSFER_INTERRUPT);
	case UE_ISOCHRONOUS:
		return (CVMX_USB_TRANSFER_ISOCHRONOUS);
	case UE_BULK:
		return (CVMX_USB_TRANSFER_BULK);
	default:
		return (0);		/* should not happen */
	}
}