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
struct stat {int /*<<< orphan*/  st_nlink; } ;
typedef  int /*<<< orphan*/  pb3 ;
typedef  int /*<<< orphan*/  pb2 ;
typedef  int /*<<< orphan*/  pb1 ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_EQ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EISDIR ; 
 scalar_t__ ENOTEMPTY ; 
 int /*<<< orphan*/  FSTYPE_MSDOS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_RUMPFS (int /*<<< orphan*/  const*) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  RL (int) ; 
 int S_IFREG ; 
 int /*<<< orphan*/  USES_DIRS ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 int /*<<< orphan*/  checkfile (char*,struct stat*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  md (char*,int,char const*,char*) ; 
 int rump_sys_mkdir (char*,int) ; 
 int rump_sys_mknod (char*,int,int) ; 
 int rump_sys_rename (char*,char*) ; 
 int rump_sys_rmdir (char*) ; 
 int rump_sys_stat (char*,struct stat*) ; 

__attribute__((used)) static void
rename_dir(const atf_tc_t *tc, const char *mp)
{
	char pb1[MAXPATHLEN], pb2[MAXPATHLEN], pb3[MAXPATHLEN];
	struct stat ref, sb;

	if (FSTYPE_RUMPFS(tc))
		atf_tc_skip("rename not supported by file system");

	USES_DIRS;

	md(pb1, sizeof(pb1), mp, "dir1");
	if (rump_sys_mkdir(pb1, 0777) == -1)
		atf_tc_fail_errno("mkdir 1");

	md(pb2, sizeof(pb2), mp, "dir2");
	if (rump_sys_mkdir(pb2, 0777) == -1)
		atf_tc_fail_errno("mkdir 2");
	md(pb2, sizeof(pb2), mp, "dir2/subdir");
	if (rump_sys_mkdir(pb2, 0777) == -1)
		atf_tc_fail_errno("mkdir 3");

	md(pb3, sizeof(pb3), mp, "dir1/file");
	if (rump_sys_mknod(pb3, S_IFREG | 0777, -1) == -1)
		atf_tc_fail_errno("create file");
	if (rump_sys_stat(pb3, &ref) == -1)
		atf_tc_fail_errno("stat of file");

	/*
	 * First try ops which should succeed.
	 */

	/* rename within directory */
	md(pb3, sizeof(pb3), mp, "dir3");
	if (rump_sys_rename(pb1, pb3) == -1)
		atf_tc_fail_errno("rename 1");
	checkfile(pb3, &ref);

	/* rename directory onto itself (two ways, should fail) */
	md(pb1, sizeof(pb1), mp, "dir3/.");
	if (rump_sys_rename(pb1, pb3) != -1 || errno != EINVAL)
		atf_tc_fail_errno("rename 2");
	if (rump_sys_rename(pb3, pb1) != -1 || errno != EISDIR)
		atf_tc_fail_errno("rename 3");

	checkfile(pb3, &ref);

	/* rename father of directory into directory */
	md(pb1, sizeof(pb1), mp, "dir2/dir");
	md(pb2, sizeof(pb2), mp, "dir2");
	if (rump_sys_rename(pb2, pb1) != -1 || errno != EINVAL)
		atf_tc_fail_errno("rename 4");

	/* same for grandfather */
	md(pb1, sizeof(pb1), mp, "dir2/subdir/dir2");
	if (rump_sys_rename(pb2, pb1) != -1 || errno != EINVAL)
		atf_tc_fail("rename 5");

	checkfile(pb3, &ref);

	/* rename directory over a non-empty directory */
	if (rump_sys_rename(pb2, pb3) != -1 || errno != ENOTEMPTY)
		atf_tc_fail("rename 6");

	/* cross-directory rename */
	md(pb1, sizeof(pb1), mp, "dir3");
	md(pb2, sizeof(pb2), mp, "dir2/somedir");
	if (rump_sys_rename(pb1, pb2) == -1)
		atf_tc_fail_errno("rename 7");
	checkfile(pb2, &ref);

	/* move to parent directory */
	md(pb1, sizeof(pb1), mp, "dir2/somedir/../../dir3");
	if (rump_sys_rename(pb2, pb1) == -1)
		atf_tc_fail_errno("rename 8");
	md(pb1, sizeof(pb1), mp, "dir2/../dir3");
	checkfile(pb1, &ref);

	/* atomic cross-directory rename */
	md(pb3, sizeof(pb3), mp, "dir2/subdir");
	if (rump_sys_rename(pb1, pb3) == -1)
		atf_tc_fail_errno("rename 9");
	checkfile(pb3, &ref);

	/* rename directory over an empty directory */
	md(pb1, sizeof(pb1), mp, "parent");
	md(pb2, sizeof(pb2), mp, "parent/dir1");
	md(pb3, sizeof(pb3), mp, "parent/dir2");
	RL(rump_sys_mkdir(pb1, 0777));
	RL(rump_sys_mkdir(pb2, 0777));
	RL(rump_sys_mkdir(pb3, 0777));
	RL(rump_sys_rename(pb2, pb3));

	RL(rump_sys_stat(pb1, &sb));
	if (! FSTYPE_MSDOS(tc))
		ATF_CHECK_EQ(sb.st_nlink, 3);
	RL(rump_sys_rmdir(pb3));
	RL(rump_sys_rmdir(pb1));
}