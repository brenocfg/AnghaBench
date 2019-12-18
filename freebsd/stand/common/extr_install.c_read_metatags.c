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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int errno ; 
 int /*<<< orphan*/  inst_kernel ; 
 int /*<<< orphan*/  inst_loader_rc ; 
 int /*<<< orphan*/  inst_modules ; 
 int /*<<< orphan*/  inst_rootfs ; 
 int read (int,char*,int) ; 
 int setmultipath (int /*<<< orphan*/ *,char*) ; 
 int setpath (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
read_metatags(int fd)
{
	char buf[1024];
	char *p, *tag, *val;
	ssize_t fsize;
	int error;

	fsize = read(fd, buf, sizeof(buf));
	if (fsize == -1)
		return (errno);

	/*
	 * Assume that if we read a whole buffer worth of data, we
	 * haven't read the entire file. In other words, the buffer
	 * size must always be larger than the file size. That way
	 * we can append a '\0' and use standard string operations.
	 * Return an error if this is not possible.
	 */
	if (fsize == sizeof(buf))
		return (ENOMEM);

	buf[fsize] = '\0';
	error = 0;
	tag = buf;
	while (!error && *tag != '\0') {
		val = strchr(tag, '=');
		if (val == NULL) {
			error = EINVAL;
			break;
		}
		*val++ = '\0';
		p = strchr(val, '\n');
		if (p == NULL) {
			error = EINVAL;
			break;
		}
		*p++ = '\0';

		if (strcmp(tag, "KERNEL") == 0)
			error = setpath(&inst_kernel, val);
		else if (strcmp(tag, "MODULES") == 0)
			error = setmultipath(&inst_modules, val);
		else if (strcmp(tag, "ROOTFS") == 0)
			error = setpath(&inst_rootfs, val);
		else if (strcmp(tag, "LOADER_RC") == 0)
			error = setpath(&inst_loader_rc, val);

		tag = p;
	}

	return (error);
}