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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct libusb20_device {TYPE_1__* methods; } ;
struct LIBUSB20_CONTROL_SETUP_DECODED {int dummy; } ;
struct TYPE_2__ {int (* do_request_sync ) (struct libusb20_device*,struct LIBUSB20_CONTROL_SETUP_DECODED*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct libusb20_device*,struct LIBUSB20_CONTROL_SETUP_DECODED*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
libusb20_dev_request_sync(struct libusb20_device *pdev,
    struct LIBUSB20_CONTROL_SETUP_DECODED *setup, void *data,
    uint16_t *pactlen, uint32_t timeout, uint8_t flags)
{
	int error;

	error = pdev->methods->do_request_sync(pdev,
	    setup, data, pactlen, timeout, flags);
	return (error);
}