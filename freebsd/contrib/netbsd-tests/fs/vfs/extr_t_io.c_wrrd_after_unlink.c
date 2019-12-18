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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  v2 ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int) ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_fsync (int) ; 
 int rump_sys_open (char*,int,int) ; 
 int rump_sys_pread (int,int*,int,int) ; 
 int rump_sys_pwrite (int,int*,int,int) ; 
 int rump_sys_unlink (char*) ; 

__attribute__((used)) static void
wrrd_after_unlink(const atf_tc_t *tc, const char *mp)
{
	int value = 0x11;
	int v2;
	int fd;

	FSTEST_ENTER();

	RL(fd = rump_sys_open("file", O_RDWR|O_CREAT, 0666));
	RL(rump_sys_unlink("file"));

	RL(rump_sys_pwrite(fd, &value, sizeof(value), 654321));

	/*
	 * We can't easily invalidate the buffer since we hold a
	 * reference, but try to get them to flush anyway.
	 */
	RL(rump_sys_fsync(fd));
	RL(rump_sys_pread(fd, &v2, sizeof(v2), 654321));
	rump_sys_close(fd);

	ATF_REQUIRE_EQ(value, v2);
	FSTEST_EXIT();
}