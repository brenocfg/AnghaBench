#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct statfs {int f_flags; int /*<<< orphan*/  f_namemax; int /*<<< orphan*/  f_version; } ;
struct mount {int mnt_flag; TYPE_1__* mnt_op; int /*<<< orphan*/  mnt_stat; } ;
struct TYPE_2__ {int (* vfs_statfs ) (struct mount*,struct statfs*) ;} ;

/* Variables and functions */
 int MNT_VISFLAGMASK ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  STATFS_VERSION ; 
 int /*<<< orphan*/  memcpy (struct statfs*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct mount*,struct statfs*) ; 

int
__vfs_statfs(struct mount *mp, struct statfs *sbp)
{

	/*
	 * Filesystems only fill in part of the structure for updates, we
	 * have to read the entirety first to get all content.
	 */
	memcpy(sbp, &mp->mnt_stat, sizeof(*sbp));

	/*
	 * Set these in case the underlying filesystem fails to do so.
	 */
	sbp->f_version = STATFS_VERSION;
	sbp->f_namemax = NAME_MAX;
	sbp->f_flags = mp->mnt_flag & MNT_VISFLAGMASK;

	return (mp->mnt_op->vfs_statfs(mp, sbp));
}