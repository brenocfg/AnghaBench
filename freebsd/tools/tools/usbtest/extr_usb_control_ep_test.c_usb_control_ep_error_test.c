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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct libusb20_device {int dummy; } ;
struct LIBUSB20_CONTROL_SETUP_DECODED {int bmRequestType; int bRequest; int wValue; int wLength; scalar_t__ wIndex; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUSB20_CONTROL_SETUP ; 
 int /*<<< orphan*/  LIBUSB20_INIT (int /*<<< orphan*/ ,struct LIBUSB20_CONTROL_SETUP_DECODED*) ; 
 struct libusb20_device* find_usb_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_dev_close (struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_dev_free (struct libusb20_device*) ; 
 int libusb20_dev_get_address (struct libusb20_device*) ; 
 int libusb20_dev_get_bus_number (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int libusb20_dev_request_sync (struct libusb20_device*,struct LIBUSB20_CONTROL_SETUP_DECODED*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_ctrl_ep_fail (int,int,int,int) ; 

void
usb_control_ep_error_test(uint16_t vid, uint16_t pid)
{
	struct LIBUSB20_CONTROL_SETUP_DECODED req;
	struct libusb20_device *pdev;
	uint8_t buffer[256];
	int error;
	int fail = 0;
	int bus;
	int dev;
	int cfg;

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

	bus = libusb20_dev_get_bus_number(pdev);
	dev = libusb20_dev_get_address(pdev);

	for (cfg = 0; cfg != 255; cfg++) {

		LIBUSB20_INIT(LIBUSB20_CONTROL_SETUP, &req);
		req.bmRequestType = 0x80; /* read */
		req.bRequest = 0x06; /* descriptor */
		req.wValue = 0x0200 | cfg; /* config descriptor */
		req.wIndex = 0;
		req.wLength = 255;

		printf("Test #%d.1/3 ...\n", cfg);

		set_ctrl_ep_fail(-1,-1,0,0);

		error = libusb20_dev_request_sync(pdev, &req, buffer,
		    NULL, 1000, 0);
		if (error != 0) {
			printf("Last configuration index is: %d\n", cfg - 1);
			break;
		}

		printf("Test #%d.2/3 ...\n", cfg);

		set_ctrl_ep_fail(bus,dev,1,1);

		error = libusb20_dev_request_sync(pdev, &req, buffer,
		    NULL, 1000, 0);

		set_ctrl_ep_fail(-1,-1,0,0);

		error = libusb20_dev_request_sync(pdev, &req, buffer,
		    NULL, 1000, 0);
		if (error != 0) {
			printf("Cannot fetch descriptor (unexpected)\n");
			fail++;
		}

		printf("Test #%d.3/3 ...\n", cfg);

		set_ctrl_ep_fail(bus,dev,0,1);

		error = libusb20_dev_request_sync(pdev, &req, buffer,
		    NULL, 1000, 0);

		set_ctrl_ep_fail(-1,-1,0,0);

		error = libusb20_dev_request_sync(pdev, &req, buffer,
		    NULL, 1000, 0);
		if (error != 0) {
			printf("Cannot fetch descriptor (unexpected)\n");
			fail++;
		}
	}

	libusb20_dev_close(pdev);
	libusb20_dev_free(pdev);

	printf("Test completed detecting %d failures\nDone\n\n", fail);
}