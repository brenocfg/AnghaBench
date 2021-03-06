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
 int /*<<< orphan*/  USBDEVFS_CLAIMINTERFACE ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 char* strerror (int) ; 

void claim_some_intf(int fd)
{
	int i, res;

	for (i = 0; i < 4; i++) {
		res = ioctl(fd, USBDEVFS_CLAIMINTERFACE, &i);
		if (!res)
			printf("OK: claimed if %d\n", i);
		else
			printf("ERROR claiming if %d (%d - %s)\n",
			       i, -res, strerror(-res));
	}
}