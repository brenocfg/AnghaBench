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
 int /*<<< orphan*/  APMIO_DISABLE ; 
 int /*<<< orphan*/  APMIO_ENABLE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
apm_enable(int fd, int enable) 
{
	if (enable) {
		if (ioctl(fd, APMIO_ENABLE) == -1)
			err(1, "ioctl(APMIO_ENABLE)");
	} else {
		if (ioctl(fd, APMIO_DISABLE) == -1)
			err(1, "ioctl(APMIO_DISABLE)");
	}
}