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
struct vnode {int /*<<< orphan*/  v_rl; int /*<<< orphan*/  v_cache_dst; int /*<<< orphan*/  v_cache_src; int /*<<< orphan*/  v_bufobj; int /*<<< orphan*/ * v_vnlock; int /*<<< orphan*/  v_interlock; int /*<<< orphan*/  v_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int LK_IS_VNODE ; 
 int LK_NOSHARE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  PVFS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLKTIMEOUT ; 
 int /*<<< orphan*/  bufobj_init (int /*<<< orphan*/ *,struct vnode*) ; 
 int /*<<< orphan*/  bzero (struct vnode*,int) ; 
 int /*<<< orphan*/  lockinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vnode_init(void *mem, int size, int flags)
{
	struct vnode *vp;

	vp = mem;
	bzero(vp, size);
	/*
	 * Setup locks.
	 */
	vp->v_vnlock = &vp->v_lock;
	mtx_init(&vp->v_interlock, "vnode interlock", NULL, MTX_DEF);
	/*
	 * By default, don't allow shared locks unless filesystems opt-in.
	 */
	lockinit(vp->v_vnlock, PVFS, "vnode", VLKTIMEOUT,
	    LK_NOSHARE | LK_IS_VNODE);
	/*
	 * Initialize bufobj.
	 */
	bufobj_init(&vp->v_bufobj, vp);
	/*
	 * Initialize namecache.
	 */
	LIST_INIT(&vp->v_cache_src);
	TAILQ_INIT(&vp->v_cache_dst);
	/*
	 * Initialize rangelocks.
	 */
	rangelock_init(&vp->v_rl);
	return (0);
}