#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  os_priv; } ;
typedef  TYPE_1__ libusb_device ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int libusb20_dev_get_port_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
libusb_get_port_path(libusb_context *ctx, libusb_device *dev, uint8_t *buf,
    uint8_t bufsize)
{
	return (libusb20_dev_get_port_path(dev->os_priv, buf, bufsize));
}