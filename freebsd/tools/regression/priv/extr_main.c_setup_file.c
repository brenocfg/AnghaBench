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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*,...) ; 
 scalar_t__ fchmod (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fchown (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
setup_file(const char *test, char *fpathp, uid_t uid, gid_t gid, mode_t mode)
{
	int fd;

	strcpy(fpathp, "/tmp/priv.XXXXXXXXXXX");
	fd = mkstemp(fpathp);
	if (fd < 0)
		err(-1, "test %s: mkstemp", test);

	if (fchown(fd, uid, gid) < 0)
		err(-1, "test %s: fchown(%s, %d, %d)", test, fpathp, uid,
		    gid);

	if (fchmod(fd, mode) < 0)
		err(-1, "test %s: chmod(%s, 0%o)", test, fpathp, mode);

	close(fd);
}