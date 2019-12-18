#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mount {TYPE_2__* mnt_vfc; } ;
struct TYPE_4__ {int /*<<< orphan*/  vfc_name; TYPE_1__* vfc_vfsops_sd; } ;
struct TYPE_3__ {int (* vfs_mount ) (struct mount*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGDEFERSTOP_SILENT ; 
 int /*<<< orphan*/  TSRAW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_ENTER ; 
 int /*<<< orphan*/  TS_EXIT ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  sigallowstop (int) ; 
 int sigdeferstop (int /*<<< orphan*/ ) ; 
 int stub1 (struct mount*) ; 

__attribute__((used)) static int
vfs_mount_sigdefer(struct mount *mp)
{
	int prev_stops, rc;

	TSRAW(curthread, TS_ENTER, "VFS_MOUNT", mp->mnt_vfc->vfc_name);
	prev_stops = sigdeferstop(SIGDEFERSTOP_SILENT);
	rc = (*mp->mnt_vfc->vfc_vfsops_sd->vfs_mount)(mp);
	sigallowstop(prev_stops);
	TSRAW(curthread, TS_EXIT, "VFS_MOUNT", mp->mnt_vfc->vfc_name);
	return (rc);
}