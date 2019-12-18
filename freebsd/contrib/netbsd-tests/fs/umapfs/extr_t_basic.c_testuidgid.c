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
typedef  scalar_t__ uid_t ;
struct stat {scalar_t__ st_uid; scalar_t__ st_gid; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_tc_fail (char*,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*,char const*) ; 
 int rump_sys_stat (char const*,struct stat*) ; 

__attribute__((used)) static void
testuidgid(const char *path, uid_t uid, gid_t gid)
{
	struct stat sb;

	if (rump_sys_stat(path, &sb) == -1)
		atf_tc_fail_errno("stat %s", path);
	if (uid != (uid_t)-1) {
		if (sb.st_uid != uid)
			atf_tc_fail("%s: expected uid %d, got %d",
			    path, uid, sb.st_uid);
	}
	if (gid != (gid_t)-1) {
		if (sb.st_gid != gid)
			atf_tc_fail("%s: expected gid %d, got %d",
			    path, gid, sb.st_gid);
	}
}