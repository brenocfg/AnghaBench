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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static char *sysfs_attr(const char *dev, const char *attr)
{
	int fd, len = 0;
	char path[PATH_MAX];
	static char buf[129];

	memset(buf, 0, sizeof(buf));
	snprintf(path, sizeof(path) - 1, "/sys/bus/usb/devices/%s/%s", dev, attr);

	if ((fd = open(path, O_RDONLY)) >= 0)
	{
		len = read(fd, buf, sizeof(buf) - 1);
		close(fd);
	}

	while (--len > 0 && isspace(buf[len]))
		buf[len] = 0;

	return (len >= 0) ? buf : NULL;
}