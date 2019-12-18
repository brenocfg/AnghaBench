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
struct libusb20_device {scalar_t__ is_opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_close (struct libusb20_device*) ; 

void
libusb20_dev_free(struct libusb20_device *pdev)
{
	if (pdev == NULL) {
		/* be NULL safe */
		return;
	}
	if (pdev->is_opened) {
		if (libusb20_dev_close(pdev)) {
			/* ignore any errors */
		}
	}
	free(pdev);
	return;
}