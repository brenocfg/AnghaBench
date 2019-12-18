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
struct vnode {int /*<<< orphan*/  v_bufobj; } ;
struct swdevt {struct vnode* sw_id; scalar_t__ sw_first; } ;
struct buf {scalar_t__ b_iocmd; scalar_t__ b_blkno; int /*<<< orphan*/  b_iooffset; struct vnode* b_vp; int /*<<< orphan*/ * b_bufobj; } ;

/* Variables and functions */
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  bstrategy (struct buf*) ; 
 int /*<<< orphan*/  bufobj_wdrop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufobj_wref (int /*<<< orphan*/ *) ; 
 scalar_t__ ctodb (scalar_t__) ; 
 int /*<<< orphan*/  dbtob (scalar_t__) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 

__attribute__((used)) static void
swapdev_strategy(struct buf *bp, struct swdevt *sp)
{
	struct vnode *vp2;

	bp->b_blkno = ctodb(bp->b_blkno - sp->sw_first);

	vp2 = sp->sw_id;
	vhold(vp2);
	if (bp->b_iocmd == BIO_WRITE) {
		if (bp->b_bufobj)
			bufobj_wdrop(bp->b_bufobj);
		bufobj_wref(&vp2->v_bufobj);
	}
	if (bp->b_bufobj != &vp2->v_bufobj)
		bp->b_bufobj = &vp2->v_bufobj;
	bp->b_vp = vp2;
	bp->b_iooffset = dbtob(bp->b_blkno);
	bstrategy(bp);
	return;
}