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
typedef  int /*<<< orphan*/  unionargs ;
struct union_args {char* target; int /*<<< orphan*/  mntflags; } ;

/* Variables and functions */
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  MOUNT_UNION ; 
 int /*<<< orphan*/  UNMNT_BELOW ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct union_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rump_sys_mkdir (char*,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct union_args*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static void
mountunion(const char *mp, char *lowerpath)
{
	struct union_args unionargs;

	sprintf(lowerpath, "/lower");
	rump_sys_mkdir(lowerpath, 0777);

	/* mount the union with our testfs as the upper layer */
	memset(&unionargs, 0, sizeof(unionargs));
	unionargs.target = lowerpath;
	unionargs.mntflags = UNMNT_BELOW;

	if (rump_sys_mount(MOUNT_UNION, mp, 0,
	    &unionargs, sizeof(unionargs)) == -1) {
		if (errno == EOPNOTSUPP) {
			atf_tc_skip("fs does not support VOP_WHITEOUT");
		} else {
			atf_tc_fail_errno("union mount");
		}
	}
}