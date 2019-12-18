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
struct usbentry {int bus_num; int dev_num; char* product_name; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  USBDEVFS_RESET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_device(struct usbentry *dev)
{
	int fd;
	char path[PATH_MAX];

	snprintf(path, sizeof(path) - 1, "/dev/bus/usb/%03d/%03d",
	         dev->bus_num, dev->dev_num);

	printf("Resetting %s ... ", dev->product_name);

	if ((fd = open(path, O_WRONLY)) > -1)
	{
		if (ioctl(fd, USBDEVFS_RESET, 0) < 0)
			printf("failed [%s]\n", strerror(errno));
		else
			printf("ok\n");

		close(fd);
	}
	else
	{
		printf("can't open [%s]\n", strerror(errno));
	}
}