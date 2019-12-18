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
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int /*<<< orphan*/  FUNSIZE ; 
 int /*<<< orphan*/  FUNTEXT ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int) ; 
 int rump_sys_close (int) ; 
 int rump_sys_open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rump_sys_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filegen(const atf_tc_t *tc, const char *mp)
{
	int fd;

	FSTEST_ENTER();
	RL(fd = rump_sys_open(AFILE, O_CREAT | O_RDWR, 0777));
	ATF_REQUIRE_EQ(rump_sys_write(fd, FUNTEXT, FUNSIZE), FUNSIZE);
	RL(rump_sys_close(fd));
	FSTEST_EXIT();
}