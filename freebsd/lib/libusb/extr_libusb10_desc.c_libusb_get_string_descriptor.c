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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 int LIBUSB_DT_STRING ; 
 int /*<<< orphan*/  LIBUSB_ENDPOINT_IN ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int /*<<< orphan*/  LIBUSB_REQUEST_GET_DESCRIPTOR ; 
 int libusb_control_transfer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int,int) ; 

int
libusb_get_string_descriptor(libusb_device_handle *pdev,
    uint8_t desc_index, uint16_t langid, unsigned char *data,
    int length)
{
	if (pdev == NULL || data == NULL || length < 1)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (length > 65535)
		length = 65535;

	/* put some default data into the destination buffer */
	data[0] = 0;

	return (libusb_control_transfer(pdev, LIBUSB_ENDPOINT_IN,
	    LIBUSB_REQUEST_GET_DESCRIPTOR, (LIBUSB_DT_STRING << 8) | desc_index,
	    langid, data, length, 1000));
}