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
typedef  int /*<<< orphan*/  libusb_device_handle ;
typedef  int /*<<< orphan*/  libusb_context ;
struct TYPE_2__ {int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GET_CONTEXT (int /*<<< orphan*/ *) ; 
 TYPE_1__* libusb_get_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static libusb_context *
libusb10_get_context_by_device_handle(libusb_device_handle *devh)
{
	libusb_context *ctx;

	if (devh != NULL)
		ctx = libusb_get_device(devh)->ctx;
	else
		ctx = NULL;

	return (GET_CONTEXT(ctx));
}