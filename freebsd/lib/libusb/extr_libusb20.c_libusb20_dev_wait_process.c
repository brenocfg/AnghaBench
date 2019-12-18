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
struct pollfd {int events; scalar_t__ revents; int /*<<< orphan*/  fd; } ;
struct libusb20_device {int /*<<< orphan*/  file; int /*<<< orphan*/  is_opened; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 

void
libusb20_dev_wait_process(struct libusb20_device *pdev, int timeout)
{
	struct pollfd pfd[1];

	if (!pdev->is_opened) {
		return;
	}
	pfd[0].fd = pdev->file;
	pfd[0].events = (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM);
	pfd[0].revents = 0;

	if (poll(pfd, 1, timeout)) {
		/* ignore any error */
	}
	return;
}