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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct vpollinfo {TYPE_1__ vpi_selinfo; int /*<<< orphan*/  vpi_lock; } ;
struct vnode {struct vpollinfo* v_pollinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  destroy_vpollinfo_free (struct vpollinfo*) ; 
 int /*<<< orphan*/  knlist_init (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vpollinfo* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_knl_assert_locked ; 
 int /*<<< orphan*/  vfs_knl_assert_unlocked ; 
 int /*<<< orphan*/  vfs_knllock ; 
 int /*<<< orphan*/  vfs_knlunlock ; 
 int /*<<< orphan*/  vnodepoll_zone ; 

void
v_addpollinfo(struct vnode *vp)
{
	struct vpollinfo *vi;

	if (vp->v_pollinfo != NULL)
		return;
	vi = uma_zalloc(vnodepoll_zone, M_WAITOK | M_ZERO);
	mtx_init(&vi->vpi_lock, "vnode pollinfo", NULL, MTX_DEF);
	knlist_init(&vi->vpi_selinfo.si_note, vp, vfs_knllock,
	    vfs_knlunlock, vfs_knl_assert_locked, vfs_knl_assert_unlocked);
	VI_LOCK(vp);
	if (vp->v_pollinfo != NULL) {
		VI_UNLOCK(vp);
		destroy_vpollinfo_free(vi);
		return;
	}
	vp->v_pollinfo = vi;
	VI_UNLOCK(vp);
}