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
struct libusb20_device {int dummy; } ;
struct LIBUSB20_DEVICE_DESC_DECODED {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP0 ; 
 int /*<<< orphan*/  LIBUSB20_DEVICE_DESC (int /*<<< orphan*/ ,struct LIBUSB20_DEVICE_DESC_DECODED*) ; 
 struct LIBUSB20_DEVICE_DESC_DECODED* libusb20_dev_get_device_desc (struct libusb20_device*) ; 

void
dump_device_desc(struct libusb20_device *pdev)
{
	struct LIBUSB20_DEVICE_DESC_DECODED *ddesc;

	ddesc = libusb20_dev_get_device_desc(pdev);
	LIBUSB20_DEVICE_DESC(DUMP0, ddesc);
	return;
}