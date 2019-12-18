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
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct vnode {int v_vflag; TYPE_1__* v_rdev; } ;
struct snapdata {int /*<<< orphan*/  sn_lock; scalar_t__ sn_listsize; int /*<<< orphan*/ * sn_blklist; int /*<<< orphan*/  sn_head; } ;
struct TYPE_2__ {struct snapdata* si_snapdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VI_LOCKED (struct vnode*,char*) ; 
 int LK_DRAIN ; 
 int LK_INTERLOCK ; 
 int LK_RELEASE ; 
 int /*<<< orphan*/  M_UFSMNT ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * VI_MTX (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int VV_COPYONWRITE ; 
 int /*<<< orphan*/  ffs_snapdata_free (struct snapdata*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
try_free_snapdata(struct vnode *devvp)
{
	struct snapdata *sn;
	ufs2_daddr_t *snapblklist;

	ASSERT_VI_LOCKED(devvp, "try_free_snapdata");
	sn = devvp->v_rdev->si_snapdata;

	if (sn == NULL || TAILQ_FIRST(&sn->sn_head) != NULL ||
	    (devvp->v_vflag & VV_COPYONWRITE) == 0) {
		VI_UNLOCK(devvp);
		return;
	}

	devvp->v_rdev->si_snapdata = NULL;
	devvp->v_vflag &= ~VV_COPYONWRITE;
	lockmgr(&sn->sn_lock, LK_DRAIN|LK_INTERLOCK, VI_MTX(devvp));
	snapblklist = sn->sn_blklist;
	sn->sn_blklist = NULL;
	sn->sn_listsize = 0;
	lockmgr(&sn->sn_lock, LK_RELEASE, NULL);
	if (snapblklist != NULL)
		free(snapblklist, M_UFSMNT);
	ffs_snapdata_free(sn);
}