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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct libusb20_device {int dummy; } ;
struct LIBUSB20_DEVICE_DESC_DECODED {int bNumConfigurations; } ;

/* Variables and functions */
 struct libusb20_device* find_usb_device (int,int) ; 
 int /*<<< orphan*/  libusb20_dev_free (struct libusb20_device*) ; 
 struct LIBUSB20_DEVICE_DESC_DECODED* libusb20_dev_get_device_desc (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int libusb20_dev_set_config_index (struct libusb20_device*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
usb_set_config_test(uint16_t vid, uint16_t pid, uint32_t duration)
{
	struct libusb20_device *pdev;
	struct LIBUSB20_DEVICE_DESC_DECODED *ddesc;
	int x;
	int error;
	int failed;
	int exp;

	pdev = find_usb_device(vid, pid);
	if (pdev == NULL) {
		printf("USB device not found\n");
		return;
	}
	error = libusb20_dev_open(pdev, 0);
	if (error) {
		printf("Could not open USB device\n");
		libusb20_dev_free(pdev);
		return;
	}
	failed = 0;

	printf("Starting set config test for "
	    "VID=0x%04x PID=0x%04x\n", vid, pid);

	for (x = 255; x > -1; x--) {

		error = libusb20_dev_set_config_index(pdev, x);
		if (error == 0) {
			if (x == 255) {
				printf("Unconfiguring USB device "
				    "was successful\n");
			} else {
				printf("Setting configuration %d "
				    "was successful\n", x);
			}
		} else {
			failed++;
		}
	}

	ddesc = libusb20_dev_get_device_desc(pdev);
	if (ddesc != NULL)
		exp = ddesc->bNumConfigurations + 1;
	else
		exp = 1;

	printf("\n\n"
	    "Set configuration summary\n"
	    "Valid count:  %d/%d %s\n"
	    "Failed count: %d\n",
	    256 - failed, exp,
	    (exp == (256 - failed)) ? "(expected)" : "(unexpected)",
	    failed);

	libusb20_dev_free(pdev);
}