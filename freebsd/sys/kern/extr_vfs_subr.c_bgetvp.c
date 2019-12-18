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
struct vnode {struct bufobj v_bufobj; } ;
struct buf {int b_xflags; struct bufobj* b_bufobj; struct vnode* b_vp; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BO_WLOCKED (struct bufobj*) ; 
 int BX_VNCLEAN ; 
 int BX_VNDIRTY ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct buf*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_BUF ; 
 int /*<<< orphan*/  VNASSERT (int,struct vnode*,char*) ; 
 int /*<<< orphan*/  buf_vlist_add (struct buf*,struct bufobj*,int) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 

void
bgetvp(struct vnode *vp, struct buf *bp)
{
	struct bufobj *bo;

	bo = &vp->v_bufobj;
	ASSERT_BO_WLOCKED(bo);
	VNASSERT(bp->b_vp == NULL, bp->b_vp, ("bgetvp: not free"));

	CTR3(KTR_BUF, "bgetvp(%p) vp %p flags %X", bp, vp, bp->b_flags);
	VNASSERT((bp->b_xflags & (BX_VNDIRTY|BX_VNCLEAN)) == 0, vp,
	    ("bgetvp: bp already attached! %p", bp));

	vhold(vp);
	bp->b_vp = vp;
	bp->b_bufobj = bo;
	/*
	 * Insert onto list for new vnode.
	 */
	buf_vlist_add(bp, bo, BX_VNCLEAN);
}