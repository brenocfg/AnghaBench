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
struct libusb_device {int /*<<< orphan*/  dev_poll; int /*<<< orphan*/ * ctx; } ;
struct libusb20_device {int dummy; } ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  libusb10_remove_pollfd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb10_wakeup_event_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb20_dev_close (struct libusb20_device*) ; 
 struct libusb_device* libusb_get_device (struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb_unref_device (struct libusb_device*) ; 

void
libusb_close(struct libusb20_device *pdev)
{
	libusb_context *ctx;
	struct libusb_device *dev;

	if (pdev == NULL)
		return;			/* be NULL safe */

	dev = libusb_get_device(pdev);
	ctx = dev->ctx;

	libusb10_remove_pollfd(ctx, &dev->dev_poll);

	libusb20_dev_close(pdev);

	/* unref will free the "pdev" when the refcount reaches zero */
	libusb_unref_device(dev);

	/* make sure our event loop detects the closed device */
	libusb10_wakeup_event_loop(ctx);
}