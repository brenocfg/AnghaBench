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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_STATUS_CANCELED ; 
 int /*<<< orphan*/  USBD_STATUS_DEVICE_GONE ; 
 int /*<<< orphan*/  USBD_STATUS_ERROR_SHORT_TRANSFER ; 
 int /*<<< orphan*/  USBD_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  USBD_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  USBD_STATUS_PENDING ; 
 int /*<<< orphan*/  USBD_STATUS_REQUEST_FAILED ; 
 int /*<<< orphan*/  USBD_STATUS_SUCCESS ; 
 int /*<<< orphan*/  USBD_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  USBD_STATUS_XACT_ERROR ; 
#define  USB_ERR_CANCELLED 138 
#define  USB_ERR_INVAL 137 
#define  USB_ERR_IOERROR 136 
#define  USB_ERR_NOMEM 135 
#define  USB_ERR_NORMAL_COMPLETION 134 
#define  USB_ERR_NOT_STARTED 133 
#define  USB_ERR_NO_POWER 132 
#define  USB_ERR_PENDING_REQUESTS 131 
#define  USB_ERR_SHORT_XFER 130 
#define  USB_ERR_TIMEOUT 129 
#define  USB_ERR_TOO_DEEP 128 

__attribute__((used)) static int32_t
usbd_usb2urb(int status)
{

	switch (status) {
	case USB_ERR_NORMAL_COMPLETION:
		return (USBD_STATUS_SUCCESS);
	case USB_ERR_PENDING_REQUESTS:
		return (USBD_STATUS_PENDING);
	case USB_ERR_TIMEOUT:
		return (USBD_STATUS_TIMEOUT);
	case USB_ERR_SHORT_XFER:
		return (USBD_STATUS_ERROR_SHORT_TRANSFER);
	case USB_ERR_IOERROR:
		return (USBD_STATUS_XACT_ERROR);
	case USB_ERR_NOMEM:
		return (USBD_STATUS_NO_MEMORY);
	case USB_ERR_INVAL:
		return (USBD_STATUS_REQUEST_FAILED);
	case USB_ERR_NOT_STARTED:
	case USB_ERR_TOO_DEEP:
	case USB_ERR_NO_POWER:
		return (USBD_STATUS_DEVICE_GONE);
	case USB_ERR_CANCELLED:
		return (USBD_STATUS_CANCELED);
	default:
		break;
	}

	return (USBD_STATUS_NOT_SUPPORTED);
}