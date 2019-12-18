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
struct msdosfs_args {int /*<<< orphan*/  version; int /*<<< orphan*/  fspec; } ;
typedef  int /*<<< orphan*/  margs ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_MSDOS ; 
 int /*<<< orphan*/  MSDOSFSMNT_VERSION ; 
 int /*<<< orphan*/  __UNCONST (char const*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  memset (struct msdosfs_args*,int /*<<< orphan*/ ,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct msdosfs_args*,int) ; 

__attribute__((used)) static void
mount_diskfs(const char *fspec, const char *path)
{
	struct msdosfs_args margs;

	memset(&margs, 0, sizeof(margs));
	margs.fspec = __UNCONST(fspec);
	margs.version = MSDOSFSMNT_VERSION;

	if (rump_sys_mount(MOUNT_MSDOS, path, 0, &margs, sizeof(margs)) == -1)
		err(1, "mount msdosfs %s", path);
}