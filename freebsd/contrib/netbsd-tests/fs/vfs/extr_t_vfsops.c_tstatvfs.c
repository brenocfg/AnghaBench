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
struct statvfs {scalar_t__ f_namemax; int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_fstypename; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_STREQ (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ FSTYPE_P2K_FFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_PUFFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ MAXNAMLEN ; 
 int /*<<< orphan*/  ST_WAIT ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 char* atf_tc_get_md_var (int /*<<< orphan*/  const*,char*) ; 
 int rump_sys_statvfs1 (char const*,struct statvfs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tstatvfs(const atf_tc_t *tc, const char *path)
{
	const char *fstype = atf_tc_get_md_var(tc, "X-fs.mntname");
	struct statvfs svb;

	if (rump_sys_statvfs1(path, &svb, ST_WAIT) == -1)
		atf_tc_fail_errno("statvfs");

	ATF_REQUIRE(svb.f_namemax > 0 && svb.f_namemax <= MAXNAMLEN);
	if (!(FSTYPE_PUFFS(tc) || FSTYPE_P2K_FFS(tc)))
		ATF_REQUIRE_STREQ(svb.f_fstypename, fstype);
	ATF_REQUIRE_STREQ(svb.f_mntonname, path);
}