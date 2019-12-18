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
typedef  int /*<<< orphan*/  pb ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  USES_DIRS ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 scalar_t__ errno ; 
 int rump_sys_mkdir (char*,int) ; 
 int rump_sys_rmdir (char*) ; 
 int rump_sys_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void
dir_simple(const atf_tc_t *tc, const char *mountpath)
{
	char pb[MAXPATHLEN];
	struct stat sb;

	USES_DIRS;

	/* check we can create directories */
	snprintf(pb, sizeof(pb), "%s/dir", mountpath);
	if (rump_sys_mkdir(pb, 0777) == -1)
		atf_tc_fail_errno("mkdir");
	if (rump_sys_stat(pb, &sb) == -1)
		atf_tc_fail_errno("stat new directory");

	/* check we can remove then and that it makes them unreachable */
	if (rump_sys_rmdir(pb) == -1)
		atf_tc_fail_errno("rmdir");
	if (rump_sys_stat(pb, &sb) != -1 || errno != ENOENT)
		atf_tc_fail("ENOENT expected from stat");
}