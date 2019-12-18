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
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ ioctl (int,unsigned long,void*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int
doit(const char *iff_name, unsigned long cmd, void *data)
{
	static int fd = 0;
	
	if (fd == 0) {
		char buf[64];
		snprintf(buf, 64, "/dev/%s", iff_name);

		if ((fd = open(buf, O_RDWR)) < 0)
			return -1;
	}
	
	return ioctl(fd, cmd, data) < 0 ? -1 : 0;
}