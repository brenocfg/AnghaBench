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
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int) ; 
 int TBSIZE ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char*,int,...) ; 
 int /*<<< orphan*/  rump_sys_read (int,char*,int) ; 
 int rump_sys_unlink (char*) ; 
 int rump_sys_unmount (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_write (int,char*,int) ; 

__attribute__((used)) static void
read_after_unlink(const atf_tc_t *tc, const char *mp)
{
	char buf[TBSIZE], buf2[TBSIZE];
	int fd;

	FSTEST_ENTER();

	/* create file and put some content into it */
	RL(fd = rump_sys_open("file", O_RDWR|O_CREAT, 0666));
	memset(buf, 'D', TBSIZE);
	ATF_REQUIRE_EQ(rump_sys_write(fd, buf, TBSIZE), TBSIZE);
	rump_sys_close(fd);

	/* flush buffers from UBC to file system */
	ATF_REQUIRE_ERRNO(EBUSY, rump_sys_unmount(mp, 0) == -1);

	RL(fd = rump_sys_open("file", O_RDWR));
	RL(rump_sys_unlink("file"));

	ATF_REQUIRE_EQ(rump_sys_read(fd, buf2, TBSIZE), TBSIZE);
	ATF_REQUIRE_EQ(memcmp(buf, buf2, TBSIZE), 0);
	rump_sys_close(fd);

	FSTEST_EXIT();
}