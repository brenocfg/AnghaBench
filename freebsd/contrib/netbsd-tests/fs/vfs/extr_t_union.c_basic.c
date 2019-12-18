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
struct stat {int dummy; } ;
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  dbuf ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int,int) ; 
 scalar_t__ DT_WHT ; 
 int ENOENT ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RL (int) ; 
 char* TFILE ; 
 struct dirent* _DIRENT_NEXT (struct dirent*) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,...) ; 
 int /*<<< orphan*/  mountunion (char const*,char*) ; 
 int rump_sys_close (int) ; 
 int rump_sys_getdents (int,char*,int) ; 
 int rump_sys_open (char const*,int /*<<< orphan*/ ) ; 
 int rump_sys_stat (char*,struct stat*) ; 
 int rump_sys_unlink (char*) ; 
 int rump_sys_unmount (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  xput_tfile (char const*,char*) ; 
 int xread_tfile (char const*,char*) ; 

__attribute__((used)) static void
basic(const atf_tc_t *tc, const char *mp)
{
	char lowerpath[MAXPATHLEN];
	char dbuf[8192];
	struct stat sb;
	struct dirent *dp;
	int error, fd, dsize;

	mountunion(mp, lowerpath);

	/* create a file in the lower layer */
	xput_tfile(lowerpath, TFILE);

	/* first, test we can read the old file from the new namespace */
	error = xread_tfile(mp, TFILE);
	if (error != 0)
		atf_tc_fail("union compare failed: %d (%s)",
		    error, strerror(error));

	/* then, test upper layer writes don't affect the lower layer */
	xput_tfile(mp, "kiekko");
	if ((error = xread_tfile(lowerpath, "kiekko")) != ENOENT)
		atf_tc_fail("invisibility failed: %d (%s)",
		    error, strerror(error));
	
	/* check that we can whiteout stuff in the upper layer */
	FSTEST_ENTER();
	RL(rump_sys_unlink(TFILE));
	ATF_REQUIRE_ERRNO(ENOENT, rump_sys_stat(TFILE, &sb) == -1);
	FSTEST_EXIT();

	/* check that the removed node is not in the directory listing */
	RL(fd = rump_sys_open(mp, O_RDONLY));
	RL(dsize = rump_sys_getdents(fd, dbuf, sizeof(dbuf)));
	for (dp = (struct dirent *)dbuf;
	    (char *)dp < dbuf + dsize;
	    dp = _DIRENT_NEXT(dp)) {
		if (strcmp(dp->d_name, TFILE) == 0 && dp->d_type != DT_WHT)
			atf_tc_fail("removed file non-white-outed");
	}
	RL(rump_sys_close(fd));

	RL(rump_sys_unmount(mp, 0));
}