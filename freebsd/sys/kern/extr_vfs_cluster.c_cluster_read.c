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
typedef  long u_quad_t ;
struct bufobj {int dummy; } ;
struct vnode {struct bufobj v_bufobj; TYPE_2__* v_mount; } ;
struct ucred {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ru_inblock; } ;
struct thread {TYPE_1__ td_ru; int /*<<< orphan*/  td_proc; } ;
struct buf {int b_flags; long b_offset; long b_bufsize; int b_blkno; void* b_iooffset; int /*<<< orphan*/ * b_iodone; int /*<<< orphan*/  b_ioflags; void* b_iocmd; } ;
typedef  long off_t ;
typedef  int daddr_t ;
struct TYPE_4__ {long mnt_iosize_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 void* BIO_READ ; 
 int /*<<< orphan*/  BO_RLOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_RUNLOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BUF_KERNPROC (struct buf*) ; 
 scalar_t__ BUF_LOCK (struct buf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 int B_ASYNC ; 
 int B_CACHE ; 
 int B_CLUSTER ; 
 int B_DELWRI ; 
 int B_INVAL ; 
 int B_RAM ; 
 int GB_NOSPARSE ; 
 int GB_UNMAPPED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 scalar_t__ NOOFFSET ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int VOP_BMAP (struct vnode*,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bqrelse (struct buf*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  bstrategy (struct buf*) ; 
 int bufwait (struct buf*) ; 
 struct buf* cluster_rbuild (struct vnode*,long,int,int,long,int,int,struct buf*) ; 
 struct thread* curthread ; 
 void* dbtob (int) ; 
 struct buf* gbincore (struct bufobj*,int) ; 
 struct buf* getblk (struct vnode*,int,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int getblkx (struct vnode*,int,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct buf**) ; 
 int howmany (long,long) ; 
 int min (int,int) ; 
 int nbuf ; 
 int /*<<< orphan*/  racct_add_buf (int /*<<< orphan*/ ,struct buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 int read_max ; 
 long read_min ; 
 int /*<<< orphan*/  unmapped_buf_allowed ; 
 int /*<<< orphan*/  vfs_busy_pages (struct buf*,int /*<<< orphan*/ ) ; 

int
cluster_read(struct vnode *vp, u_quad_t filesize, daddr_t lblkno, long size,
    struct ucred *cred, long totread, int seqcount, int gbflags,
    struct buf **bpp)
{
	struct buf *bp, *rbp, *reqbp;
	struct bufobj *bo;
	struct thread *td;
	daddr_t blkno, origblkno;
	int maxra, racluster;
	int error, ncontig;
	int i;

	error = 0;
	td = curthread;
	bo = &vp->v_bufobj;
	if (!unmapped_buf_allowed)
		gbflags &= ~GB_UNMAPPED;

	/*
	 * Try to limit the amount of read-ahead by a few
	 * ad-hoc parameters.  This needs work!!!
	 */
	racluster = vp->v_mount->mnt_iosize_max / size;
	maxra = seqcount;
	maxra = min(read_max, maxra);
	maxra = min(nbuf/8, maxra);
	if (((u_quad_t)(lblkno + maxra + 1) * size) > filesize)
		maxra = (filesize / size) - lblkno;

	/*
	 * get the requested block
	 */
	error = getblkx(vp, lblkno, size, 0, 0, gbflags, &bp);
	if (error != 0) {
		*bpp = NULL;
		return (error);
	}
	gbflags &= ~GB_NOSPARSE;
	origblkno = lblkno;
	*bpp = reqbp = bp;

	/*
	 * if it is in the cache, then check to see if the reads have been
	 * sequential.  If they have, then try some read-ahead, otherwise
	 * back-off on prospective read-aheads.
	 */
	if (bp->b_flags & B_CACHE) {
		if (!seqcount) {
			return 0;
		} else if ((bp->b_flags & B_RAM) == 0) {
			return 0;
		} else {
			bp->b_flags &= ~B_RAM;
			BO_RLOCK(bo);
			for (i = 1; i < maxra; i++) {
				/*
				 * Stop if the buffer does not exist or it
				 * is invalid (about to go away?)
				 */
				rbp = gbincore(&vp->v_bufobj, lblkno+i);
				if (rbp == NULL || (rbp->b_flags & B_INVAL))
					break;

				/*
				 * Set another read-ahead mark so we know 
				 * to check again. (If we can lock the
				 * buffer without waiting)
				 */
				if ((((i % racluster) == (racluster - 1)) ||
				    (i == (maxra - 1))) 
				    && (0 == BUF_LOCK(rbp, 
					LK_EXCLUSIVE | LK_NOWAIT, NULL))) {
					rbp->b_flags |= B_RAM;
					BUF_UNLOCK(rbp);
				}			
			}
			BO_RUNLOCK(bo);
			if (i >= maxra) {
				return 0;
			}
			lblkno += i;
		}
		reqbp = bp = NULL;
	/*
	 * If it isn't in the cache, then get a chunk from
	 * disk if sequential, otherwise just get the block.
	 */
	} else {
		off_t firstread = bp->b_offset;
		int nblks;
		long minread;

		KASSERT(bp->b_offset != NOOFFSET,
		    ("cluster_read: no buffer offset"));

		ncontig = 0;

		/*
		 * Adjust totread if needed
		 */
		minread = read_min * size;
		if (minread > totread)
			totread = minread;

		/*
		 * Compute the total number of blocks that we should read
		 * synchronously.
		 */
		if (firstread + totread > filesize)
			totread = filesize - firstread;
		nblks = howmany(totread, size);
		if (nblks > racluster)
			nblks = racluster;

		/*
		 * Now compute the number of contiguous blocks.
		 */
		if (nblks > 1) {
	    		error = VOP_BMAP(vp, lblkno, NULL,
				&blkno, &ncontig, NULL);
			/*
			 * If this failed to map just do the original block.
			 */
			if (error || blkno == -1)
				ncontig = 0;
		}

		/*
		 * If we have contiguous data available do a cluster
		 * otherwise just read the requested block.
		 */
		if (ncontig) {
			/* Account for our first block. */
			ncontig = min(ncontig + 1, nblks);
			if (ncontig < nblks)
				nblks = ncontig;
			bp = cluster_rbuild(vp, filesize, lblkno,
			    blkno, size, nblks, gbflags, bp);
			lblkno += (bp->b_bufsize / size);
		} else {
			bp->b_flags |= B_RAM;
			bp->b_iocmd = BIO_READ;
			lblkno += 1;
		}
	}

	/*
	 * handle the synchronous read so that it is available ASAP.
	 */
	if (bp) {
		if ((bp->b_flags & B_CLUSTER) == 0) {
			vfs_busy_pages(bp, 0);
		}
		bp->b_flags &= ~B_INVAL;
		bp->b_ioflags &= ~BIO_ERROR;
		if ((bp->b_flags & B_ASYNC) || bp->b_iodone != NULL)
			BUF_KERNPROC(bp);
		bp->b_iooffset = dbtob(bp->b_blkno);
		bstrategy(bp);
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(td->td_proc);
			racct_add_buf(td->td_proc, bp, 0);
			PROC_UNLOCK(td->td_proc);
		}
#endif /* RACCT */
		td->td_ru.ru_inblock++;
	}

	/*
	 * If we have been doing sequential I/O, then do some read-ahead.
	 */
	while (lblkno < (origblkno + maxra)) {
		error = VOP_BMAP(vp, lblkno, NULL, &blkno, &ncontig, NULL);
		if (error)
			break;

		if (blkno == -1)
			break;

		/*
		 * We could throttle ncontig here by maxra but we might as
		 * well read the data if it is contiguous.  We're throttled
		 * by racluster anyway.
		 */
		if (ncontig) {
			ncontig = min(ncontig + 1, racluster);
			rbp = cluster_rbuild(vp, filesize, lblkno, blkno,
			    size, ncontig, gbflags, NULL);
			lblkno += (rbp->b_bufsize / size);
			if (rbp->b_flags & B_DELWRI) {
				bqrelse(rbp);
				continue;
			}
		} else {
			rbp = getblk(vp, lblkno, size, 0, 0, gbflags);
			lblkno += 1;
			if (rbp->b_flags & B_DELWRI) {
				bqrelse(rbp);
				continue;
			}
			rbp->b_flags |= B_ASYNC | B_RAM;
			rbp->b_iocmd = BIO_READ;
			rbp->b_blkno = blkno;
		}
		if (rbp->b_flags & B_CACHE) {
			rbp->b_flags &= ~B_ASYNC;
			bqrelse(rbp);
			continue;
		}
		if ((rbp->b_flags & B_CLUSTER) == 0) {
			vfs_busy_pages(rbp, 0);
		}
		rbp->b_flags &= ~B_INVAL;
		rbp->b_ioflags &= ~BIO_ERROR;
		if ((rbp->b_flags & B_ASYNC) || rbp->b_iodone != NULL)
			BUF_KERNPROC(rbp);
		rbp->b_iooffset = dbtob(rbp->b_blkno);
		bstrategy(rbp);
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(td->td_proc);
			racct_add_buf(td->td_proc, rbp, 0);
			PROC_UNLOCK(td->td_proc);
		}
#endif /* RACCT */
		td->td_ru.ru_inblock++;
	}

	if (reqbp) {
		/*
		 * Like bread, always brelse() the buffer when
		 * returning an error.
		 */
		error = bufwait(reqbp);
		if (error != 0) {
			brelse(reqbp);
			*bpp = NULL;
		}
	}
	return (error);
}