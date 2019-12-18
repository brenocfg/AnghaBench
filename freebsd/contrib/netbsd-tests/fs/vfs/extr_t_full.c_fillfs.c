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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 size_t FSTEST_IMGSIZE ; 
 scalar_t__ FSTYPE_NFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_P2K_FFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_PUFFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_RUMPFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_ZFS (int /*<<< orphan*/  const*) ; 
 size_t NFSBONUS ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  atf_tc_expect_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int rump_sys_chdir (char const*) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char*,int) ; 
 size_t rump_sys_write (int,char*,int) ; 

__attribute__((used)) static void
fillfs(const atf_tc_t *tc, const char *mp)
{
	char buf[8192];
	size_t written;
	ssize_t n = 0; /* xxxgcc */
	size_t bonus;
	int fd, i = 0;

	if (FSTYPE_P2K_FFS(tc) || FSTYPE_PUFFS(tc) || FSTYPE_RUMPFS(tc)) {
		atf_tc_skip("fs does not support explicit block allocation "
		    "(GOP_ALLOC)");
	}

	bonus = 0;
	if (FSTYPE_NFS(tc))
		bonus = NFSBONUS;

	if (rump_sys_chdir(mp) == -1)
		atf_tc_fail_errno("chdir mountpoint");
	fd = rump_sys_open("afile", O_CREAT | O_RDWR);
	if (fd == -1)
		atf_tc_fail_errno("create file");

	for (written = 0; written < FSTEST_IMGSIZE + bonus; written +=n) {
		memset(buf, i++, sizeof(buf)); /* known garbage */
		n = rump_sys_write(fd, buf, sizeof(buf));
		if (n == -1)
			break;
	}
	if (FSTYPE_ZFS(tc))
		atf_tc_expect_fail("PR kern/47656: Test known to be broken");
	if (n == -1) {
		if (errno != ENOSPC)
			atf_tc_fail_errno("write");
	} else {
		atf_tc_fail("filled file system over size limit");
	}

	rump_sys_close(fd);
	rump_sys_chdir("/");
}