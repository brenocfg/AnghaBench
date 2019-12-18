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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 

int
libusb_alloc_streams(libusb_device_handle *dev, uint32_t num_streams,
    unsigned char *endpoints, int num_endpoints)
{
	if (num_streams > 1)
		return (LIBUSB_ERROR_INVALID_PARAM);
	return (0);
}