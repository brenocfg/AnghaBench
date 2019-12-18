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
 int ENOSYS ; 
 int O_CREAT ; 
 scalar_t__ cap_rights_limit (int,int /*<<< orphan*/ *) ; 
 int capflags ; 
 int /*<<< orphan*/  capmode ; 
 int /*<<< orphan*/ * caprightsp ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char const*,int,...) ; 

__attribute__((used)) static int
open_file(const char *name)
{
	int fd, serrno;

	if ((capflags & O_CREAT) == 0)
		fd = open(name, capflags);
	else
		fd = open(name, capflags, capmode);
	if (fd < 0)
		return (-1);

	if (caprightsp != NULL) {
		if (cap_rights_limit(fd, caprightsp) < 0 && errno != ENOSYS) {
			serrno = errno;
			close(fd);
			errno = serrno;
			return (-1);
		}
	}

	return (fd);
}