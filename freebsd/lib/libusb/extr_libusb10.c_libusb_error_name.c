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

/* Variables and functions */
#define  LIBUSB_ERROR_ACCESS 141 
#define  LIBUSB_ERROR_BUSY 140 
#define  LIBUSB_ERROR_INTERRUPTED 139 
#define  LIBUSB_ERROR_INVALID_PARAM 138 
#define  LIBUSB_ERROR_IO 137 
#define  LIBUSB_ERROR_NOT_FOUND 136 
#define  LIBUSB_ERROR_NOT_SUPPORTED 135 
#define  LIBUSB_ERROR_NO_DEVICE 134 
#define  LIBUSB_ERROR_NO_MEM 133 
#define  LIBUSB_ERROR_OTHER 132 
#define  LIBUSB_ERROR_OVERFLOW 131 
#define  LIBUSB_ERROR_PIPE 130 
#define  LIBUSB_ERROR_TIMEOUT 129 
#define  LIBUSB_SUCCESS 128 

const char *
libusb_error_name(int code)
{
	switch (code) {
	case LIBUSB_SUCCESS:
		return ("LIBUSB_SUCCESS");
	case LIBUSB_ERROR_IO:
		return ("LIBUSB_ERROR_IO");
	case LIBUSB_ERROR_INVALID_PARAM:
		return ("LIBUSB_ERROR_INVALID_PARAM");
	case LIBUSB_ERROR_ACCESS:
		return ("LIBUSB_ERROR_ACCESS");
	case LIBUSB_ERROR_NO_DEVICE:
		return ("LIBUSB_ERROR_NO_DEVICE");
	case LIBUSB_ERROR_NOT_FOUND:
		return ("LIBUSB_ERROR_NOT_FOUND");
	case LIBUSB_ERROR_BUSY:
		return ("LIBUSB_ERROR_BUSY");
	case LIBUSB_ERROR_TIMEOUT:
		return ("LIBUSB_ERROR_TIMEOUT");
	case LIBUSB_ERROR_OVERFLOW:
		return ("LIBUSB_ERROR_OVERFLOW");
	case LIBUSB_ERROR_PIPE:
		return ("LIBUSB_ERROR_PIPE");
	case LIBUSB_ERROR_INTERRUPTED:
		return ("LIBUSB_ERROR_INTERRUPTED");
	case LIBUSB_ERROR_NO_MEM:
		return ("LIBUSB_ERROR_NO_MEM");
	case LIBUSB_ERROR_NOT_SUPPORTED:
		return ("LIBUSB_ERROR_NOT_SUPPORTED");
	case LIBUSB_ERROR_OTHER:
		return ("LIBUSB_ERROR_OTHER");
	default:
		return ("LIBUSB_ERROR_UNKNOWN");
	}
}