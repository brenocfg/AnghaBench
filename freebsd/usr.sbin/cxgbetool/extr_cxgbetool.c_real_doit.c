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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int errno ; 
 int ioctl (int,unsigned long,void*) ; 
 char* nexus ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
real_doit(unsigned long cmd, void *data, const char *cmdstr)
{
	static int fd = -1;
	int rc = 0;

	if (fd == -1) {
		char buf[64];

		snprintf(buf, sizeof(buf), "/dev/%s", nexus);
		if ((fd = open(buf, O_RDWR)) < 0) {
			warn("open(%s)", nexus);
			rc = errno;
			return (rc);
		}
	}

	rc = ioctl(fd, cmd, data);
	if (rc < 0) {
		warn("%s", cmdstr);
		rc = errno;
	}

	return (rc);
}