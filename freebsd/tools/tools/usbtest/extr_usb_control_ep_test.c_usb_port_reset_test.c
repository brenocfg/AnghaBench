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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 struct libusb20_device* find_usb_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_check_connected (struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_dev_free (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_reset (struct libusb20_device*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  usleep (int) ; 

void
usb_port_reset_test(uint16_t vid, uint16_t pid, uint32_t duration)
{
	struct timeval sub_tv;
	struct timeval ref_tv;
	struct timeval res_tv;

	struct libusb20_device *pdev;

	int error;
	int iter;
	int errcnt;

	time_t last_sec;

	/* sysctl() - no set config */

	pdev = find_usb_device(vid, pid);
	if (pdev == NULL) {
		printf("USB device not found\n");
		return;
	}
	error = libusb20_dev_open(pdev, 0);
	if (error) {
		libusb20_dev_free(pdev);
		printf("Could not open USB device\n");
		return;
	}
	iter = 0;

	errcnt = 0;

	gettimeofday(&ref_tv, 0);

	last_sec = ref_tv.tv_sec;

	while (1) {

		gettimeofday(&sub_tv, 0);

		if (last_sec != sub_tv.tv_sec) {

			printf("STATUS: ID=%u, ERR=%u\n",
			    (int)iter, (int)errcnt);

			fflush(stdout);

			last_sec = sub_tv.tv_sec;
		}
		timersub(&sub_tv, &ref_tv, &res_tv);

		if ((res_tv.tv_sec < 0) || (res_tv.tv_sec >= (int)duration))
			break;

		if (libusb20_dev_reset(pdev)) {
			errcnt++;
			usleep(50000);
		}
		if (libusb20_dev_check_connected(pdev) != 0) {
			printf("Device disconnected\n");
			break;
		}
		iter++;
	}

	libusb20_dev_reset(pdev);

	libusb20_dev_free(pdev);
}