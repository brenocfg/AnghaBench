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
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_RSYNC ; 
 int O_SYNC ; 
 int /*<<< orphan*/  RL (int) ; 
 int rump_sys_close (int) ; 
 int rump_sys_open (char*,int,...) ; 
 int rump_sys_read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rump_sys_write (int,char*,int) ; 

__attribute__((used)) static void
read_fault(const atf_tc_t *tc, const char *mp)
{
	char ch = 123;
	int fd;

	FSTEST_ENTER();
	RL(fd = rump_sys_open("file", O_CREAT | O_RDWR, 0777));
	ATF_REQUIRE_EQ(rump_sys_write(fd, &ch, 1), 1);
	RL(rump_sys_close(fd));
	RL(fd = rump_sys_open("file", O_RDONLY | O_SYNC | O_RSYNC));
	ATF_REQUIRE_ERRNO(EFAULT, rump_sys_read(fd, NULL, 1) == -1);
	RL(rump_sys_close(fd));
	FSTEST_EXIT();
}