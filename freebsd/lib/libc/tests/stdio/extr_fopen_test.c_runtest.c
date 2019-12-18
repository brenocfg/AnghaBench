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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 int CORRECT_O_ACCMODE ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int O_APPEND ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static void
runtest(const char *fname, const char *mode)
{
	FILE *fp;
	int exp_fget_ret, fget_ret, fd, flags, wantedflags;

	fp = fopen(fname, mode);
	ATF_REQUIRE_MSG(fp != NULL,
	    "fopen(\"%s\", \"%s\") failed", fname, mode);
	fd = fileno(fp);
	ATF_REQUIRE_MSG(fd >= 0, "fileno() failed for fopen");
	exp_fget_ret = strchr(mode, 'e') != NULL ? FD_CLOEXEC : 0;
	ATF_REQUIRE_MSG((fget_ret = fcntl(fd, F_GETFD)) == exp_fget_ret,
	    "fcntl(.., F_GETFD) didn't FD_CLOEXEC as expected %d != %d",
	    exp_fget_ret, fget_ret);
	flags = fcntl(fd, F_GETFL);
	if (strchr(mode, '+'))
		wantedflags = O_RDWR | (*mode == 'a' ? O_APPEND : 0);
	else if (*mode == 'r')
		wantedflags = O_RDONLY;
	else if (*mode == 'w')
		wantedflags = O_WRONLY;
	else if (*mode == 'a')
		wantedflags = O_WRONLY | O_APPEND;
	else
		wantedflags = -1;
	fclose(fp);
	if (wantedflags == -1)
		atf_tc_fail("unrecognized mode: %s", mode);
	else if ((flags & (CORRECT_O_ACCMODE | O_APPEND)) != wantedflags)
		atf_tc_fail("incorrect access mode: %s", mode);
}