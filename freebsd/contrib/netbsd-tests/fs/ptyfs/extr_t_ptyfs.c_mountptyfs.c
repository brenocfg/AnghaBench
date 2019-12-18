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
struct ptyfs_args {int mode; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  MOUNT_PTYFS ; 
 int /*<<< orphan*/  PTYFS_ARGSVERSION ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct ptyfs_args*,int /*<<< orphan*/ ,int) ; 
 int rump_sys_mkdir (char*,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char const*,int,struct ptyfs_args*,int) ; 

__attribute__((used)) static void
mountptyfs(const char *mp, int flags)
{
	struct ptyfs_args args;

	if (rump_sys_mkdir("/mp", 0777) == -1) {
		if (errno != EEXIST)
			atf_tc_fail_errno("mp1");
	}
	memset(&args, 0, sizeof(args));
	args.version = PTYFS_ARGSVERSION;
	args.mode = 0777;
	if (rump_sys_mount(MOUNT_PTYFS, mp, flags, &args, sizeof(args)) == -1)
		atf_tc_fail_errno("could not mount ptyfs");
}