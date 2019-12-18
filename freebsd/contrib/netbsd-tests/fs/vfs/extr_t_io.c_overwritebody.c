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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  REQUIRE_LIBC (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RL (int) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int rump_sys_close (int) ; 
 int rump_sys_ftruncate (int,int /*<<< orphan*/ ) ; 
 int rump_sys_open (char*,int,...) ; 
 int /*<<< orphan*/  rump_sys_write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
overwritebody(const atf_tc_t *tc, off_t count, bool dotrunc)
{
	char *buf;
	int fd;

	REQUIRE_LIBC(buf = malloc(count), NULL);
	FSTEST_ENTER();
	RL(fd = rump_sys_open("testi", O_CREAT | O_RDWR, 0666));
	ATF_REQUIRE_EQ(rump_sys_write(fd, buf, count), count);
	RL(rump_sys_close(fd));

	RL(fd = rump_sys_open("testi", O_RDWR));
	if (dotrunc)
		RL(rump_sys_ftruncate(fd, 0));
	ATF_REQUIRE_EQ(rump_sys_write(fd, buf, count), count);
	RL(rump_sys_close(fd));
	FSTEST_EXIT();
}