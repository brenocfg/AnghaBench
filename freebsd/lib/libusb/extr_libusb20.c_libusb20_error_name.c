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
#define  LIBUSB20_ERROR_ACCESS 141 
#define  LIBUSB20_ERROR_BUSY 140 
#define  LIBUSB20_ERROR_INTERRUPTED 139 
#define  LIBUSB20_ERROR_INVALID_PARAM 138 
#define  LIBUSB20_ERROR_IO 137 
#define  LIBUSB20_ERROR_NOT_FOUND 136 
#define  LIBUSB20_ERROR_NOT_SUPPORTED 135 
#define  LIBUSB20_ERROR_NO_DEVICE 134 
#define  LIBUSB20_ERROR_NO_MEM 133 
#define  LIBUSB20_ERROR_OTHER 132 
#define  LIBUSB20_ERROR_OVERFLOW 131 
#define  LIBUSB20_ERROR_PIPE 130 
#define  LIBUSB20_ERROR_TIMEOUT 129 
#define  LIBUSB20_SUCCESS 128 

const char *
libusb20_error_name(int code)
{
	switch (code) {
	case LIBUSB20_SUCCESS:
		return ("LIBUSB20_SUCCESS");
	case LIBUSB20_ERROR_IO:
		return ("LIBUSB20_ERROR_IO");
	case LIBUSB20_ERROR_INVALID_PARAM:
		return ("LIBUSB20_ERROR_INVALID_PARAM");
	case LIBUSB20_ERROR_ACCESS:
		return ("LIBUSB20_ERROR_ACCESS");
	case LIBUSB20_ERROR_NO_DEVICE:
		return ("LIBUSB20_ERROR_NO_DEVICE");
	case LIBUSB20_ERROR_NOT_FOUND:
		return ("LIBUSB20_ERROR_NOT_FOUND");
	case LIBUSB20_ERROR_BUSY:
		return ("LIBUSB20_ERROR_BUSY");
	case LIBUSB20_ERROR_TIMEOUT:
		return ("LIBUSB20_ERROR_TIMEOUT");
	case LIBUSB20_ERROR_OVERFLOW:
		return ("LIBUSB20_ERROR_OVERFLOW");
	case LIBUSB20_ERROR_PIPE:
		return ("LIBUSB20_ERROR_PIPE");
	case LIBUSB20_ERROR_INTERRUPTED:
		return ("LIBUSB20_ERROR_INTERRUPTED");
	case LIBUSB20_ERROR_NO_MEM:
		return ("LIBUSB20_ERROR_NO_MEM");
	case LIBUSB20_ERROR_NOT_SUPPORTED:
		return ("LIBUSB20_ERROR_NOT_SUPPORTED");
	case LIBUSB20_ERROR_OTHER:
		return ("LIBUSB20_ERROR_OTHER");
	default:
		return ("LIBUSB20_ERROR_UNKNOWN");
	}
}