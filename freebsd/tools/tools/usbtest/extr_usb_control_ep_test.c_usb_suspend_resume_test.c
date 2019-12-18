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
typedef  unsigned int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct libusb20_device {int dummy; } ;
typedef  int /*<<< orphan*/  ptimo ;

/* Variables and functions */
 int LIBUSB20_POWER_ON ; 
 int LIBUSB20_POWER_SAVE ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 struct libusb20_device* find_usb_device (int,int) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_check_connected (struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_dev_free (struct libusb20_device*) ; 
 int libusb20_dev_get_power_mode (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int libusb20_dev_set_power_mode (struct libusb20_device*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 scalar_t__ usb_ts_rand_noise () ; 
 int /*<<< orphan*/  usleep (int) ; 

void
usb_suspend_resume_test(uint16_t vid, uint16_t pid, uint32_t duration)
{
	struct timeval sub_tv;
	struct timeval ref_tv;
	struct timeval res_tv;

	struct libusb20_device *pdev;

	time_t last_sec;

	int iter;
	int error;
	int ptimo;
	int errcnt;
	int power_old;

	ptimo = 1;			/* second(s) */

	error = sysctlbyname("hw.usb.power_timeout", NULL, NULL,
	    &ptimo, sizeof(ptimo));

	if (error != 0) {
		printf("WARNING: Could not set power "
		    "timeout to 1 (error=%d) \n", errno);
	}
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
	power_old = libusb20_dev_get_power_mode(pdev);

	printf("Starting suspend and resume "
	    "test for VID=0x%04x PID=0x%04x\n", vid, pid);

	iter = 0;
	errcnt = 0;

	gettimeofday(&ref_tv, 0);

	last_sec = ref_tv.tv_sec;

	while (1) {

		if (libusb20_dev_check_connected(pdev) != 0) {
			printf("Device disconnected\n");
			break;
		}
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

		error = libusb20_dev_set_power_mode(pdev, (iter & 1) ?
		    LIBUSB20_POWER_ON : LIBUSB20_POWER_SAVE);

		if (error)
			errcnt++;

		/* wait before switching power mode */
		usleep(4100000 +
		    (((uint32_t)usb_ts_rand_noise()) % 2000000U));

		iter++;
	}

	/* restore default power mode */
	libusb20_dev_set_power_mode(pdev, power_old);

	libusb20_dev_free(pdev);
}