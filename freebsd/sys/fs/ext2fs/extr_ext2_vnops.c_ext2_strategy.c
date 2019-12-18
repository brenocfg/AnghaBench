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
struct vop_strategy_args {struct vnode* a_vp; struct buf* a_bp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;
struct bufobj {int dummy; } ;
struct buf {scalar_t__ b_blkno; scalar_t__ b_lblkno; int b_error; int /*<<< orphan*/  b_iooffset; int /*<<< orphan*/  b_ioflags; } ;
typedef  scalar_t__ daddr_t ;
struct TYPE_4__ {struct bufobj* um_bo; } ;
struct TYPE_3__ {int i_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  BO_STRATEGY (struct bufobj*,struct buf*) ; 
 int IN_E4EXTENTS ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 TYPE_2__* VFSTOEXT2 (int /*<<< orphan*/ ) ; 
 TYPE_1__* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 int /*<<< orphan*/  dbtob (scalar_t__) ; 
 int ext2_bmaparray (struct vnode*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ext4_bmapext (struct vnode*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vfs_bio_clrbuf (struct buf*) ; 

__attribute__((used)) static int
ext2_strategy(struct vop_strategy_args *ap)
{
	struct buf *bp = ap->a_bp;
	struct vnode *vp = ap->a_vp;
	struct bufobj *bo;
	daddr_t blkno;
	int error;

	if (vp->v_type == VBLK || vp->v_type == VCHR)
		panic("ext2_strategy: spec");
	if (bp->b_blkno == bp->b_lblkno) {

		if (VTOI(ap->a_vp)->i_flag & IN_E4EXTENTS)
			error = ext4_bmapext(vp, bp->b_lblkno, &blkno, NULL, NULL);
		else
			error = ext2_bmaparray(vp, bp->b_lblkno, &blkno, NULL, NULL);

		bp->b_blkno = blkno;
		if (error) {
			bp->b_error = error;
			bp->b_ioflags |= BIO_ERROR;
			bufdone(bp);
			return (0);
		}
		if ((long)bp->b_blkno == -1)
			vfs_bio_clrbuf(bp);
	}
	if ((long)bp->b_blkno == -1) {
		bufdone(bp);
		return (0);
	}
	bp->b_iooffset = dbtob(bp->b_blkno);
	bo = VFSTOEXT2(vp->v_mount)->um_bo;
	BO_STRATEGY(bo, bp);
	return (0);
}