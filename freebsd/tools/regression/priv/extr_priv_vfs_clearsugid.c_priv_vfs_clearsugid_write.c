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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EA_DATA ; 
 int /*<<< orphan*/  EA_SIZE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  confirm_sugid (char*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char*,char*) ; 
 int /*<<< orphan*/  fpath ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
priv_vfs_clearsugid_write(int asroot, int injail, struct test *test)
{
	int fd;

	fd = open(fpath, O_RDWR);
	if (fd < 0)
		err(-1, "priv_vfs_clearsugid_write(%s, %s): open",
		    asroot ? "root" : "!root", injail ? "jail" : "!jail");
	if (write(fd, EA_DATA, EA_SIZE) < 0)
		err(-1, "priv_vfs_clearsugid_write(%s, %s): write",
		    asroot ? "root" : "!root", injail ? "jail" : "!jail");
	(void)close(fd);
	confirm_sugid("priv_vfs_clearsugid_write", asroot, injail);
}