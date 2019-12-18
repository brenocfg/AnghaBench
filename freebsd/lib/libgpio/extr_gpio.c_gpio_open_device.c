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
typedef  int gpio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOMAXPIN ; 
 int GPIO_INVALID_HANDLE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

gpio_handle_t
gpio_open_device(const char *device)
{
	int fd, maxpins;
	int serr;

	fd = open(device, O_RDONLY);
	if (fd < 0)
		return (GPIO_INVALID_HANDLE);
	/*
	 * Check whether a simple ioctl works.
	 */
	if (ioctl(fd, GPIOMAXPIN, &maxpins) < 0) {
		serr = errno;
		close(fd);
		errno = serr;
		return (GPIO_INVALID_HANDLE);
	}

	return (fd);
}