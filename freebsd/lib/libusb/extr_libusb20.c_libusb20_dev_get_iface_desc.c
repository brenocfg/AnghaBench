#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct libusb20_device {TYPE_1__* beMethods; } ;
struct TYPE_2__ {int (* dev_get_iface_desc ) (struct libusb20_device*,scalar_t__,char*,scalar_t__) ;} ;

/* Variables and functions */
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int stub1 (struct libusb20_device*,scalar_t__,char*,scalar_t__) ; 

int
libusb20_dev_get_iface_desc(struct libusb20_device *pdev, 
    uint8_t iface_index, char *buf, uint8_t len)
{
	if ((buf == NULL) || (len == 0))
		return (LIBUSB20_ERROR_INVALID_PARAM);

	buf[0] = 0;		/* set default string value */

	return (pdev->beMethods->dev_get_iface_desc(
	    pdev, iface_index, buf, len));
}