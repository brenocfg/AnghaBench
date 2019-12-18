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
struct libusb20_device {int port_level; int parent_address; int parent_port; int /*<<< orphan*/  port_path; } ;

/* Variables and functions */
 int LIBUSB20_ERROR_OVERFLOW ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

int
libusb20_dev_get_port_path(struct libusb20_device *pdev, uint8_t *buf, uint8_t bufsize)
{

	if (pdev->port_level == 0) {
		/*
		 * Fallback for backends without port path:
		 */
		if (bufsize < 2)
			return (LIBUSB20_ERROR_OVERFLOW);
		buf[0] = pdev->parent_address;
		buf[1] = pdev->parent_port;
		return (2);
	}

	/* check if client buffer is too small */
	if (pdev->port_level > bufsize)
		return (LIBUSB20_ERROR_OVERFLOW);

	/* copy port number information */
	memcpy(buf, pdev->port_path, pdev->port_level);

	return (pdev->port_level);	/* success */
}