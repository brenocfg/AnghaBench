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
struct libusb20_device {int dummy; } ;
struct libusb20_backend {TYPE_1__* methods; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit_backend ) (struct libusb20_backend*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct libusb20_backend*) ; 
 int /*<<< orphan*/  libusb20_be_dequeue_device (struct libusb20_backend*,struct libusb20_device*) ; 
 struct libusb20_device* libusb20_be_device_foreach (struct libusb20_backend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb20_dev_free (struct libusb20_device*) ; 
 int /*<<< orphan*/  stub1 (struct libusb20_backend*) ; 

void
libusb20_be_free(struct libusb20_backend *pbe)
{
	struct libusb20_device *pdev;

	if (pbe == NULL) {
		/* be NULL safe */
		return;
	}
	while ((pdev = libusb20_be_device_foreach(pbe, NULL))) {
		libusb20_be_dequeue_device(pbe, pdev);
		libusb20_dev_free(pdev);
	}
	if (pbe->methods->exit_backend) {
		pbe->methods->exit_backend(pbe);
	}
	/* free backend */
	free(pbe);
}