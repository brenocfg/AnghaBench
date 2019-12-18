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

/* Variables and functions */
#define  LIBUSB20_TRANSFER_CANCELLED 134 
#define  LIBUSB20_TRANSFER_COMPLETED 133 
#define  LIBUSB20_TRANSFER_NO_DEVICE 132 
#define  LIBUSB20_TRANSFER_OVERFLOW 131 
#define  LIBUSB20_TRANSFER_STALL 130 
#define  LIBUSB20_TRANSFER_START 129 
#define  LIBUSB20_TRANSFER_TIMED_OUT 128 
 int LIBUSB_TRANSFER_CANCELLED ; 
 int LIBUSB_TRANSFER_COMPLETED ; 
 int LIBUSB_TRANSFER_ERROR ; 
 int LIBUSB_TRANSFER_NO_DEVICE ; 
 int LIBUSB_TRANSFER_OVERFLOW ; 
 int LIBUSB_TRANSFER_STALL ; 
 int LIBUSB_TRANSFER_TIMED_OUT ; 

__attribute__((used)) static int
libusb10_convert_error(uint8_t status)
{
	;				/* indent fix */

	switch (status) {
	case LIBUSB20_TRANSFER_START:
	case LIBUSB20_TRANSFER_COMPLETED:
		return (LIBUSB_TRANSFER_COMPLETED);
	case LIBUSB20_TRANSFER_OVERFLOW:
		return (LIBUSB_TRANSFER_OVERFLOW);
	case LIBUSB20_TRANSFER_NO_DEVICE:
		return (LIBUSB_TRANSFER_NO_DEVICE);
	case LIBUSB20_TRANSFER_STALL:
		return (LIBUSB_TRANSFER_STALL);
	case LIBUSB20_TRANSFER_CANCELLED:
		return (LIBUSB_TRANSFER_CANCELLED);
	case LIBUSB20_TRANSFER_TIMED_OUT:
		return (LIBUSB_TRANSFER_TIMED_OUT);
	default:
		return (LIBUSB_TRANSFER_ERROR);
	}
}