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
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int) ; 
 int verify_fd (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
verify_open(const char *path, int flags)
{
	int fd;
	int rc;

	if ((fd = open(path, flags)) >= 0) {
		if ((rc = verify_fd(fd, path, 0, NULL)) < 0) {
			close(fd);
			fd = rc;
		}
	}
	return (fd);
}