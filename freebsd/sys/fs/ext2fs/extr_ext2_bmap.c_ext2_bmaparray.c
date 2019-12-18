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
struct vnode {int /*<<< orphan*/  v_bufobj; struct mount* v_mount; } ;
struct mount {int mnt_iosize_max; } ;
struct inode {size_t* i_db; size_t* i_ib; int i_flags; } ;
struct indir {size_t in_off; size_t in_lbn; } ;
struct ext2mount {size_t um_seqinc; int /*<<< orphan*/  um_e2fs; } ;
struct buf {int b_flags; scalar_t__ b_data; void* b_blkno; int /*<<< orphan*/  b_iooffset; int /*<<< orphan*/  b_ioflags; int /*<<< orphan*/  b_iocmd; } ;
typedef  size_t e2fs_lbn_t ;
typedef  size_t e2fs_daddr_t ;
typedef  size_t daddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  ru_inblock; } ;
struct TYPE_4__ {TYPE_1__ td_ru; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  BIO_READ ; 
 int B_CACHE ; 
 int B_INVAL ; 
 int EXT2_BLOCK_SIZE (int /*<<< orphan*/ ) ; 
 size_t EXT2_NDADDR ; 
 int /*<<< orphan*/  EXT2_NIADDR ; 
 size_t MNINDIR (struct ext2mount*) ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int SF_SNAPSHOT ; 
 struct ext2mount* VFSTOEXT2 (struct mount*) ; 
 struct inode* VTOI (struct vnode*) ; 
 void* blkptrtodb (struct ext2mount*,size_t) ; 
 int /*<<< orphan*/  bqrelse (struct buf*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  bstrategy (struct buf*) ; 
 int bufwait (struct buf*) ; 
 int /*<<< orphan*/  curproc ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  dbtob (void*) ; 
 int ext2_getlbns (struct vnode*,size_t,struct indir*,int*) ; 
 struct buf* getblk (struct vnode*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incore (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ is_sequential (struct ext2mount*,size_t,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  racct_add_buf (int /*<<< orphan*/ ,struct buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  vfs_busy_pages (struct buf*,int /*<<< orphan*/ ) ; 

int
ext2_bmaparray(struct vnode *vp, daddr_t bn, daddr_t *bnp, int *runp, int *runb)
{
	struct inode *ip;
	struct buf *bp;
	struct ext2mount *ump;
	struct mount *mp;
	struct indir a[EXT2_NIADDR + 1], *ap;
	daddr_t daddr;
	e2fs_lbn_t metalbn;
	int error, num, maxrun = 0, bsize;
	int *nump;

	ap = NULL;
	ip = VTOI(vp);
	mp = vp->v_mount;
	ump = VFSTOEXT2(mp);

	bsize = EXT2_BLOCK_SIZE(ump->um_e2fs);

	if (runp) {
		maxrun = mp->mnt_iosize_max / bsize - 1;
		*runp = 0;
	}
	if (runb)
		*runb = 0;


	ap = a;
	nump = &num;
	error = ext2_getlbns(vp, bn, ap, nump);
	if (error)
		return (error);

	num = *nump;
	if (num == 0) {
		*bnp = blkptrtodb(ump, ip->i_db[bn]);
		if (*bnp == 0) {
			*bnp = -1;
		} else if (runp) {
			daddr_t bnb = bn;

			for (++bn; bn < EXT2_NDADDR && *runp < maxrun &&
			    is_sequential(ump, ip->i_db[bn - 1], ip->i_db[bn]);
			    ++bn, ++*runp);
			bn = bnb;
			if (runb && (bn > 0)) {
				for (--bn; (bn >= 0) && (*runb < maxrun) &&
					is_sequential(ump, ip->i_db[bn],
						ip->i_db[bn + 1]);
						--bn, ++*runb);
			}
		}
		return (0);
	}

	/* Get disk address out of indirect block array */
	daddr = ip->i_ib[ap->in_off];

	for (bp = NULL, ++ap; --num; ++ap) {
		/*
		 * Exit the loop if there is no disk address assigned yet and
		 * the indirect block isn't in the cache, or if we were
		 * looking for an indirect block and we've found it.
		 */

		metalbn = ap->in_lbn;
		if ((daddr == 0 && !incore(&vp->v_bufobj, metalbn)) || metalbn == bn)
			break;
		/*
		 * If we get here, we've either got the block in the cache
		 * or we have a disk address for it, go fetch it.
		 */
		if (bp)
			bqrelse(bp);

		bp = getblk(vp, metalbn, bsize, 0, 0, 0);
		if ((bp->b_flags & B_CACHE) == 0) {
#ifdef INVARIANTS
			if (!daddr)
				panic("ext2_bmaparray: indirect block not in cache");
#endif
			bp->b_blkno = blkptrtodb(ump, daddr);
			bp->b_iocmd = BIO_READ;
			bp->b_flags &= ~B_INVAL;
			bp->b_ioflags &= ~BIO_ERROR;
			vfs_busy_pages(bp, 0);
			bp->b_iooffset = dbtob(bp->b_blkno);
			bstrategy(bp);
#ifdef RACCT
			if (racct_enable) {
				PROC_LOCK(curproc);
				racct_add_buf(curproc, bp, 0);
				PROC_UNLOCK(curproc);
			}
#endif
			curthread->td_ru.ru_inblock++;
			error = bufwait(bp);
			if (error) {
				brelse(bp);
				return (error);
			}
		}

		daddr = ((e2fs_daddr_t *)bp->b_data)[ap->in_off];
		if (num == 1 && daddr && runp) {
			for (bn = ap->in_off + 1;
			    bn < MNINDIR(ump) && *runp < maxrun &&
			    is_sequential(ump,
			    ((e2fs_daddr_t *)bp->b_data)[bn - 1],
			    ((e2fs_daddr_t *)bp->b_data)[bn]);
			    ++bn, ++*runp);
			bn = ap->in_off;
			if (runb && bn) {
				for (--bn; bn >= 0 && *runb < maxrun &&
					is_sequential(ump,
					((e2fs_daddr_t *)bp->b_data)[bn],
					((e2fs_daddr_t *)bp->b_data)[bn + 1]);
					--bn, ++*runb);
			}
		}
	}
	if (bp)
		bqrelse(bp);

	/*
	 * Since this is FFS independent code, we are out of scope for the
	 * definitions of BLK_NOCOPY and BLK_SNAP, but we do know that they
	 * will fall in the range 1..um_seqinc, so we use that test and
	 * return a request for a zeroed out buffer if attempts are made
	 * to read a BLK_NOCOPY or BLK_SNAP block.
	 */
	if ((ip->i_flags & SF_SNAPSHOT) && daddr > 0 && daddr < ump->um_seqinc) {
		*bnp = -1;
		return (0);
	}
	*bnp = blkptrtodb(ump, daddr);
	if (*bnp == 0) {
		*bnp = -1;
	}
	return (0);
}