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
struct bufobj {int dummy; } ;
struct vnode {struct bufobj v_bufobj; int /*<<< orphan*/  v_interlock; int /*<<< orphan*/  v_vnlock; int /*<<< orphan*/  v_rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCKPTR (struct bufobj*) ; 
 int /*<<< orphan*/  lockdestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rangelock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vnode_fini(void *mem, int size)
{
	struct vnode *vp;
	struct bufobj *bo;

	vp = mem;
	rangelock_destroy(&vp->v_rl);
	lockdestroy(vp->v_vnlock);
	mtx_destroy(&vp->v_interlock);
	bo = &vp->v_bufobj;
	rw_destroy(BO_LOCKPTR(bo));
}