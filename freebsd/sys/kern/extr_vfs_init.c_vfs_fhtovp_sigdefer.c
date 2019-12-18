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
struct vnode {int dummy; } ;
struct mount {TYPE_2__* mnt_vfc; } ;
struct fid {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vfc_vfsops_sd; } ;
struct TYPE_3__ {int (* vfs_fhtovp ) (struct mount*,struct fid*,int,struct vnode**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGDEFERSTOP_SILENT ; 
 int /*<<< orphan*/  sigallowstop (int) ; 
 int sigdeferstop (int /*<<< orphan*/ ) ; 
 int stub1 (struct mount*,struct fid*,int,struct vnode**) ; 

__attribute__((used)) static int
vfs_fhtovp_sigdefer(struct mount *mp, struct fid *fidp, int flags,
    struct vnode **vpp)
{
	int prev_stops, rc;

	prev_stops = sigdeferstop(SIGDEFERSTOP_SILENT);
	rc = (*mp->mnt_vfc->vfc_vfsops_sd->vfs_fhtovp)(mp, fidp, flags, vpp);
	sigallowstop(prev_stops);
	return (rc);
}