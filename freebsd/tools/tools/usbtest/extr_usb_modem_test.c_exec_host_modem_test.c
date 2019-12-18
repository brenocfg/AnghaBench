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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct modem {scalar_t__ duration; scalar_t__ data_stress_test; scalar_t__ control_ep_test; scalar_t__ errors; scalar_t__ usb_iface; struct libusb20_device* usb_dev; void* xfer_out; void* xfer_in; scalar_t__ use_vendor_specific; } ;
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 struct libusb20_device* find_usb_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_usb_endpoints (struct libusb20_device*,int,int,int,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ libusb20_dev_detach_kernel_driver (struct libusb20_device*,scalar_t__) ; 
 int /*<<< orphan*/  libusb20_dev_free (struct libusb20_device*) ; 
 char* libusb20_dev_get_desc (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_open (struct libusb20_device*,int) ; 
 void* libusb20_tr_get_pointer (struct libusb20_device*,int) ; 
 int libusb20_tr_open (void*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  usb_modem_control_ep_test (struct modem*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usb_modem_data_stress_test (struct modem*,scalar_t__) ; 

__attribute__((used)) static void
exec_host_modem_test(struct modem *p, uint16_t vid, uint16_t pid)
{
	struct libusb20_device *pdev;

	uint8_t ntest = 0;
	uint8_t x;
	uint8_t in_ep;
	uint8_t out_ep;
	uint8_t iface;

	int error;

	pdev = find_usb_device(vid, pid);
	if (pdev == NULL) {
		printf("USB device not found\n");
		return;
	}

	if (p->use_vendor_specific)
		find_usb_endpoints(pdev, 255, 255, 255, 0, &iface, &in_ep, &out_ep, 0);
	else
		find_usb_endpoints(pdev, 2, 2, 1, 0, &iface, &in_ep, &out_ep, 1);

	if ((in_ep == 0) || (out_ep == 0)) {
		printf("Could not find USB endpoints\n");
		libusb20_dev_free(pdev);
		return;
	}
	printf("Attaching to: %s @ iface %d\n",
	    libusb20_dev_get_desc(pdev), iface);

	if (libusb20_dev_open(pdev, 2)) {
		printf("Could not open USB device\n");
		libusb20_dev_free(pdev);
		return;
	}
	if (libusb20_dev_detach_kernel_driver(pdev, iface)) {
		printf("WARNING: Could not detach kernel driver\n");
	}
	p->xfer_in = libusb20_tr_get_pointer(pdev, 0);
	error = libusb20_tr_open(p->xfer_in, 65536 / 4, 1, in_ep);
	if (error) {
		printf("Could not open USB endpoint %d\n", in_ep);
		libusb20_dev_free(pdev);
		return;
	}
	p->xfer_out = libusb20_tr_get_pointer(pdev, 1);
	error = libusb20_tr_open(p->xfer_out, 65536 / 4, 1, out_ep);
	if (error) {
		printf("Could not open USB endpoint %d\n", out_ep);
		libusb20_dev_free(pdev);
		return;
	}
	p->usb_dev = pdev;
	p->usb_iface = iface;
	p->errors = 0;

	if (p->control_ep_test)
		ntest += 7;

	if (p->data_stress_test)
		ntest += 1;

	if (ntest == 0) {
		printf("No tests selected\n");
	} else {

		if (p->control_ep_test) {
			for (x = 1; x != 8; x++) {
				usb_modem_control_ep_test(p,
				    (p->duration + ntest - 1) / ntest, x);
			}
		}
		if (p->data_stress_test) {
			usb_modem_data_stress_test(p,
			    (p->duration + ntest - 1) / ntest);
		}
	}

	printf("\nDone\n");

	libusb20_dev_free(pdev);
}