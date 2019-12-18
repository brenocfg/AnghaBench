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
typedef  int /*<<< orphan*/  pb ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int,int) ; 
 int ENOENT ; 
 int ESTALE ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 scalar_t__ FSTYPE_NFS (int /*<<< orphan*/  const*) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  RL (int) ; 
 int /*<<< orphan*/  USES_DIRS ; 
 int /*<<< orphan*/  md (char*,int,char const*,char*) ; 
 int rump_sys_chdir (char*) ; 
 int rump_sys_mkdir (char*,int) ; 
 int rump_sys_rmdir (char*) ; 

__attribute__((used)) static void
dir_rmdirdotdot(const atf_tc_t *tc, const char *mp)
{
	char pb[MAXPATHLEN];
	int xerrno;

	USES_DIRS;

	FSTEST_ENTER();
	RL(rump_sys_mkdir("test", 0777));
	RL(rump_sys_chdir("test"));

	RL(rump_sys_mkdir("subtest", 0777));
	RL(rump_sys_chdir("subtest"));

	md(pb, sizeof(pb), mp, "test/subtest");
	RL(rump_sys_rmdir(pb));
	md(pb, sizeof(pb), mp, "test");
	RL(rump_sys_rmdir(pb));

	if (FSTYPE_NFS(tc))
		xerrno = ESTALE;
	else
		xerrno = ENOENT;
	ATF_REQUIRE_ERRNO(xerrno, rump_sys_chdir("..") == -1);
	FSTEST_EXIT();
}