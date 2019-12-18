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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_STREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int) ; 
 int /*<<< orphan*/  TESTSTR ; 
 int TESTSZ ; 
 int rump_sys_close (int) ; 
 int rump_sys_fstat (int,struct stat*) ; 
 int rump_sys_ftruncate (int,int) ; 
 int rump_sys_open (char*,int) ; 
 int /*<<< orphan*/  rump_sys_pread (int,char*,int,int) ; 
 int /*<<< orphan*/  rump_sys_write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
extendbody(const atf_tc_t *tc, off_t seekcnt)
{
	char buf[TESTSZ+1];
	struct stat sb;
	int fd;

	FSTEST_ENTER();
	RL(fd = rump_sys_open("testfile",
	    O_CREAT | O_RDWR | (seekcnt ? O_APPEND : 0)));
	RL(rump_sys_ftruncate(fd, seekcnt));
	RL(rump_sys_fstat(fd, &sb));
	ATF_REQUIRE_EQ(sb.st_size, seekcnt);

	ATF_REQUIRE_EQ(rump_sys_write(fd, TESTSTR, TESTSZ), TESTSZ);
	ATF_REQUIRE_EQ(rump_sys_pread(fd, buf, TESTSZ, seekcnt), TESTSZ);
	ATF_REQUIRE_STREQ(buf, TESTSTR);

	RL(rump_sys_fstat(fd, &sb));
	ATF_REQUIRE_EQ(sb.st_size, (off_t)TESTSZ + seekcnt);
	RL(rump_sys_close(fd));
	FSTEST_EXIT();
}