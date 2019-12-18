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
struct TYPE_2__ {scalar_t__ bv_cnt; } ;
struct bufobj {scalar_t__ bo_numoutput; TYPE_1__ bo_dirty; } ;
struct vnode {struct bufobj v_bufobj; } ;
struct mount {scalar_t__ mnt_secondary_writes; int mnt_secondary_accwrites; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BO_WLOCKED (struct bufobj*) ; 
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_MTX (struct mount*) ; 
 int PDROP ; 
 int PUSER ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

int
softdep_check_suspend(struct mount *mp,
		      struct vnode *devvp,
		      int softdep_depcnt,
		      int softdep_accdepcnt,
		      int secondary_writes,
		      int secondary_accwrites)
{
	struct bufobj *bo;
	int error;
	
	(void) softdep_depcnt,
	(void) softdep_accdepcnt;

	bo = &devvp->v_bufobj;
	ASSERT_BO_WLOCKED(bo);

	MNT_ILOCK(mp);
	while (mp->mnt_secondary_writes != 0) {
		BO_UNLOCK(bo);
		msleep(&mp->mnt_secondary_writes, MNT_MTX(mp),
		    (PUSER - 1) | PDROP, "secwr", 0);
		BO_LOCK(bo);
		MNT_ILOCK(mp);
	}

	/*
	 * Reasons for needing more work before suspend:
	 * - Dirty buffers on devvp.
	 * - Secondary writes occurred after start of vnode sync loop
	 */
	error = 0;
	if (bo->bo_numoutput > 0 ||
	    bo->bo_dirty.bv_cnt > 0 ||
	    secondary_writes != 0 ||
	    mp->mnt_secondary_writes != 0 ||
	    secondary_accwrites != mp->mnt_secondary_accwrites)
		error = EAGAIN;
	BO_UNLOCK(bo);
	return (error);
}