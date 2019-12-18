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

/* Variables and functions */
 int /*<<< orphan*/  USBDEVFS_RESET ; 
 int ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int) ; 

void reset_device(int fd)
{
	int res;

	res = ioctl(fd, USBDEVFS_RESET);
	if (!res)
		printf("OK: USBDEVFS_RESET succeeded\n");
	else
		printf("ERROR: reset failed! (%d - %s)\n",
		       -res, strerror(-res));
}