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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFILE ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_STREQ (char*,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EROFS ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 scalar_t__ FSTYPE_NFSRO (int /*<<< orphan*/  const*) ; 
 int FUNSIZE ; 
 int /*<<< orphan*/  FUNTEXT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  RL (int) ; 
 int rump_sys_close (int) ; 
 int rump_sys_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_read (int,char*,int) ; 

__attribute__((used)) static void
fileio(const atf_tc_t *tc, const char *mp)
{
	int fd;
	char buf[FUNSIZE+1];
	int expected;

	if (FSTYPE_NFSRO(tc))
		expected = EACCES;
	else
		expected = EROFS;

	FSTEST_ENTER();
	RL(fd = rump_sys_open(AFILE, O_RDONLY));
	ATF_REQUIRE_EQ(rump_sys_read(fd, buf, FUNSIZE), FUNSIZE);
	buf[FUNSIZE] = '\0';
	ATF_REQUIRE_STREQ(buf, FUNTEXT);
	RL(rump_sys_close(fd));

	ATF_REQUIRE_ERRNO(expected, rump_sys_open(AFILE, O_WRONLY) == -1);
	ATF_REQUIRE_ERRNO(expected, rump_sys_open(AFILE, O_RDWR) == -1);
	FSTEST_EXIT();
}