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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_OTHER ; 
 scalar_t__ libusb20_dev_req_string_simple_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int strlen (char*) ; 

int
libusb_get_string_descriptor_ascii(libusb_device_handle *pdev,
    uint8_t desc_index, unsigned char *data, int length)
{
	if (pdev == NULL || data == NULL || length < 1)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (length > 65535)
		length = 65535;

	/* put some default data into the destination buffer */
	data[0] = 0;

	if (libusb20_dev_req_string_simple_sync(pdev, desc_index,
	    data, length) == 0)
		return (strlen((char *)data));

	return (LIBUSB_ERROR_OTHER);
}