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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTEMPTY ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MNT_RDONLY ; 
 int /*<<< orphan*/  RL (int) ; 
 int /*<<< orphan*/  TDFILE ; 
 int /*<<< orphan*/  TDIR ; 
 int ffs_fstest_mount (int /*<<< orphan*/  const*,void*,char*,int /*<<< orphan*/ ) ; 
 int ffs_fstest_newfs (int /*<<< orphan*/  const*,void**,char*,int,int /*<<< orphan*/ *) ; 
 int ffs_fstest_unmount (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mountunion (char const*,char*) ; 
 int rump_sys_chdir (char*) ; 
 int rump_sys_mkdir (int /*<<< orphan*/ ,int) ; 
 int rump_sys_rmdir (int /*<<< orphan*/ ) ; 
 int rump_sys_stat (int /*<<< orphan*/ ,struct stat*) ; 
 int rump_sys_unmount (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
whiteout(const atf_tc_t *tc, const char *mp)
{
	char lower[MAXPATHLEN];
	struct stat sb;
	void *fsarg;

	/*
	 * XXX: use ffs here to make sure any screwups in rumpfs don't
	 * affect the test
	 */
	RL(ffs_fstest_newfs(tc, &fsarg, "daimage", 1024*1024*5, NULL));
	RL(ffs_fstest_mount(tc, fsarg, "/lower", 0));

	/* create a file in the lower layer */
	RL(rump_sys_chdir("/lower"));
	RL(rump_sys_mkdir(TDIR, 0777));
	RL(rump_sys_mkdir(TDFILE, 0777));
	RL(rump_sys_chdir("/"));

	RL(ffs_fstest_unmount(tc, "/lower", 0));
	RL(ffs_fstest_mount(tc, fsarg, "/lower", MNT_RDONLY));

	mountunion(mp, lower);

	FSTEST_ENTER();
	ATF_REQUIRE_ERRNO(ENOTEMPTY, rump_sys_rmdir(TDIR) == -1);
	RL(rump_sys_rmdir(TDFILE));
	RL(rump_sys_rmdir(TDIR));
	ATF_REQUIRE_ERRNO(ENOENT, rump_sys_stat(TDFILE, &sb) == -1);
	ATF_REQUIRE_ERRNO(ENOENT, rump_sys_stat(TDIR, &sb) == -1);

	RL(rump_sys_mkdir(TDIR, 0777));
	RL(rump_sys_stat(TDIR, &sb));
	ATF_REQUIRE_ERRNO(ENOENT, rump_sys_stat(TDFILE, &sb) == -1);
	FSTEST_EXIT();

	RL(rump_sys_unmount(mp, 0));
}