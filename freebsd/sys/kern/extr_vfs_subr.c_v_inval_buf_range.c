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
struct bufobj {int bo_bsize; } ;
struct vnode {struct bufobj v_bufobj; } ;
typedef  int off_t ;
typedef  int daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  OFF_TO_IDX (int) ; 
 int PAGE_SIZE ; 
 scalar_t__ v_inval_buf_range_locked (struct vnode*,struct bufobj*,int,int) ; 
 int /*<<< orphan*/  vn_pages_remove (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
v_inval_buf_range(struct vnode *vp, daddr_t startlbn, daddr_t endlbn,
    int blksize)
{
	struct bufobj *bo;
	off_t start, end;

	ASSERT_VOP_LOCKED(vp, "v_inval_buf_range");

	start = blksize * startlbn;
	end = blksize * endlbn;

	bo = &vp->v_bufobj;
	BO_LOCK(bo);
	MPASS(blksize == bo->bo_bsize);

	while (v_inval_buf_range_locked(vp, bo, startlbn, endlbn) == EAGAIN)
		;

	BO_UNLOCK(bo);
	vn_pages_remove(vp, OFF_TO_IDX(start), OFF_TO_IDX(end + PAGE_SIZE - 1));
}