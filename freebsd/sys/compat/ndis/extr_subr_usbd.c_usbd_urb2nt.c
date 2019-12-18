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
typedef  int int32_t ;

/* Variables and functions */
 int STATUS_CANCELLED ; 
 int STATUS_DEVICE_NOT_CONNECTED ; 
 int STATUS_FAILURE ; 
 int STATUS_NOT_IMPLEMENTED ; 
 int STATUS_NOT_SUPPORTED ; 
 int STATUS_NO_MEMORY ; 
 int STATUS_PENDING ; 
 int STATUS_SUCCESS ; 
#define  USBD_STATUS_CANCELED 134 
#define  USBD_STATUS_DEVICE_GONE 133 
#define  USBD_STATUS_NOT_SUPPORTED 132 
#define  USBD_STATUS_NO_MEMORY 131 
#define  USBD_STATUS_PENDING 130 
#define  USBD_STATUS_REQUEST_FAILED 129 
#define  USBD_STATUS_SUCCESS 128 

__attribute__((used)) static int32_t
usbd_urb2nt(int32_t status)
{

	switch (status) {
	case USBD_STATUS_SUCCESS:
		return (STATUS_SUCCESS);
	case USBD_STATUS_DEVICE_GONE:
		return (STATUS_DEVICE_NOT_CONNECTED);
	case USBD_STATUS_PENDING:
		return (STATUS_PENDING);
	case USBD_STATUS_NOT_SUPPORTED:
		return (STATUS_NOT_IMPLEMENTED);
	case USBD_STATUS_NO_MEMORY:
		return (STATUS_NO_MEMORY);
	case USBD_STATUS_REQUEST_FAILED:
		return (STATUS_NOT_SUPPORTED);
	case USBD_STATUS_CANCELED:
		return (STATUS_CANCELLED);
	default:
		break;
	}

	return (STATUS_FAILURE);
}