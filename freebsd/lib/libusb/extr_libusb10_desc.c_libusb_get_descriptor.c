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
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUSB_ENDPOINT_IN ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int /*<<< orphan*/  LIBUSB_REQUEST_GET_DESCRIPTOR ; 
 int libusb_control_transfer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int,int) ; 

int
libusb_get_descriptor(libusb_device_handle * devh, uint8_t desc_type, 
    uint8_t desc_index, uint8_t *data, int length)
{
	if (devh == NULL || data == NULL || length < 1)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (length > 65535)
		length = 65535;

	return (libusb_control_transfer(devh, LIBUSB_ENDPOINT_IN,
	    LIBUSB_REQUEST_GET_DESCRIPTOR, (desc_type << 8) | desc_index, 0, data,
	    length, 1000));
}