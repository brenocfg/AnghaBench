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
struct vop_strategy_args {int /*<<< orphan*/  a_vp; struct buf* a_bp; } ;
struct denode {TYPE_1__* de_pmp; } ;
struct bufobj {int dummy; } ;
struct buf {int b_blkno; int b_lblkno; int b_error; int /*<<< orphan*/  b_iooffset; int /*<<< orphan*/  b_ioflags; } ;
typedef  int daddr_t ;
struct TYPE_2__ {struct bufobj* pm_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  BO_STRATEGY (struct bufobj*,struct buf*) ; 
 struct denode* VTODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 int /*<<< orphan*/  dbtob (int) ; 
 int pcbmap (struct denode*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_bio_clrbuf (struct buf*) ; 

__attribute__((used)) static int
msdosfs_strategy(struct vop_strategy_args *ap)
{
	struct buf *bp = ap->a_bp;
	struct denode *dep = VTODE(ap->a_vp);
	struct bufobj *bo;
	int error = 0;
	daddr_t blkno;

	/*
	 * If we don't already know the filesystem relative block number
	 * then get it using pcbmap().  If pcbmap() returns the block
	 * number as -1 then we've got a hole in the file.  DOS filesystems
	 * don't allow files with holes, so we shouldn't ever see this.
	 */
	if (bp->b_blkno == bp->b_lblkno) {
		error = pcbmap(dep, bp->b_lblkno, &blkno, 0, 0);
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
	if (bp->b_blkno == -1) {
		bufdone(bp);
		return (0);
	}
	/*
	 * Read/write the block from/to the disk that contains the desired
	 * file block.
	 */
	bp->b_iooffset = dbtob(bp->b_blkno);
	bo = dep->de_pmp->pm_bo;
	BO_STRATEGY(bo, bp);
	return (0);
}