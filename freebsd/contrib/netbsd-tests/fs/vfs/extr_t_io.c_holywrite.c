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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  REQUIRE_LIBC (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RL (int) ; 
 size_t getpagesize () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char*,int,int) ; 
 int rump_sys_pread (int,char*,size_t,int /*<<< orphan*/ ) ; 
 int rump_sys_pwrite (int,char*,int,int) ; 

__attribute__((used)) static void
holywrite(const atf_tc_t *tc, const char *mp)
{
	char buf[1024];
	char *b2, *b3;
	size_t therange = getpagesize()+1;
	int fd;

	FSTEST_ENTER();

	RL(fd = rump_sys_open("file", O_RDWR|O_CREAT|O_TRUNC, 0666));

	memset(buf, 'A', sizeof(buf));
	RL(rump_sys_pwrite(fd, buf, 1, getpagesize()));

	memset(buf, 'B', sizeof(buf));
	RL(rump_sys_pwrite(fd, buf, 2, getpagesize()-1));

	REQUIRE_LIBC(b2 = malloc(2 * getpagesize()), NULL);
	REQUIRE_LIBC(b3 = malloc(2 * getpagesize()), NULL);

	RL(rump_sys_pread(fd, b2, therange, 0));

	memset(b3, 0, therange);
	memset(b3 + getpagesize() - 1, 'B', 2);

	ATF_REQUIRE_EQ(memcmp(b2, b3, therange), 0);

	rump_sys_close(fd);
	FSTEST_EXIT();
}