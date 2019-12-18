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
struct libusb20_device {int /*<<< orphan*/  beMethods; } ;
struct libusb20_backend {int /*<<< orphan*/  usb_devs; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_entry ; 

void
libusb20_be_enqueue_device(struct libusb20_backend *pbe, struct libusb20_device *pdev)
{
	pdev->beMethods = pbe->methods;	/* copy backend methods */
	TAILQ_INSERT_TAIL(&(pbe->usb_devs), pdev, dev_entry);
}