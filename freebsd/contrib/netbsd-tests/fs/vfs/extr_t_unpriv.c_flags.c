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
struct stat {int st_flags; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 scalar_t__ EOPNOTSUPP ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 scalar_t__ FSTYPE_ZFS (int /*<<< orphan*/  const*) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RUMP_RFCFDG ; 
 int UF_IMMUTABLE ; 
 int /*<<< orphan*/  atf_tc_expect_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  rump_pub_lwproc_releaselwp () ; 
 int /*<<< orphan*/  rump_pub_lwproc_rfork (int /*<<< orphan*/ ) ; 
 int rump_sys_chflags (char const*,int) ; 
 int rump_sys_close (int) ; 
 int rump_sys_open (char const*,int,int) ; 
 int rump_sys_setuid (int) ; 
 int rump_sys_stat (char const*,struct stat*) ; 
 int rump_sys_unlink (char const*) ; 

__attribute__((used)) static void
flags(const atf_tc_t *tc, const char *mp)
{
	const char *name = "file.test";
	int fd, fflags;
	struct stat st;

	FSTEST_ENTER();

	if ((fd = rump_sys_open(name, O_RDWR|O_CREAT, 0666)) == -1)
		atf_tc_fail_errno("open");
	if (rump_sys_close(fd) == -1)
		atf_tc_fail_errno("close");

	if (rump_sys_stat(name, &st) == -1)
		atf_tc_fail_errno("stat");
	if (FSTYPE_ZFS(tc))
		atf_tc_expect_fail("PR kern/47656: Test known to be broken");
	if (rump_sys_chflags(name, st.st_flags) == -1) {
		if (errno == EOPNOTSUPP)
			atf_tc_skip("file flags not supported by file system");
		atf_tc_fail_errno("chflags");
	}

	fflags = st.st_flags | UF_IMMUTABLE;

	rump_pub_lwproc_rfork(RUMP_RFCFDG);
	if (rump_sys_setuid(1) == -1)
		atf_tc_fail_errno("setuid");
	fflags |= UF_IMMUTABLE;
	if (rump_sys_chflags(name, fflags) != -1 || errno != EPERM)
		atf_tc_fail_errno("chflags");
	rump_pub_lwproc_releaselwp();

	if (rump_sys_chflags(name, fflags) == -1)
		atf_tc_fail_errno("chflags");

	fflags &= ~UF_IMMUTABLE;
	if (rump_sys_chflags(name, fflags) == -1)
		atf_tc_fail_errno("chflags");

	if (rump_sys_unlink(name) == -1)
		atf_tc_fail_errno("unlink");

	FSTEST_EXIT();
}