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
libusb_strerror(int code)
{
	switch (code) {
	case LIBUSB_SUCCESS:
		return ("Success");
	case LIBUSB_ERROR_IO:
		return ("I/O error");
	case LIBUSB_ERROR_INVALID_PARAM:
		return ("Invalid parameter");
	case LIBUSB_ERROR_ACCESS:
		return ("Permissions error");
	case LIBUSB_ERROR_NO_DEVICE:
		return ("No device");
	case LIBUSB_ERROR_NOT_FOUND:
		return ("Not found");
	case LIBUSB_ERROR_BUSY:
		return ("Device busy");
	case LIBUSB_ERROR_TIMEOUT:
		return ("Timeout");
	case LIBUSB_ERROR_OVERFLOW:
		return ("Overflow");
	case LIBUSB_ERROR_PIPE:
		return ("Pipe error");
	case LIBUSB_ERROR_INTERRUPTED:
		return ("Interrupted");
	case LIBUSB_ERROR_NO_MEM:
		return ("Out of memory");
	case LIBUSB_ERROR_NOT_SUPPORTED:
		return ("Not supported");
	case LIBUSB_ERROR_OTHER:
		return ("Other error");
	default:
		return ("Unknown error");
	}
}