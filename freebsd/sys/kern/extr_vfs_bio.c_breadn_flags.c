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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ru_inblock; } ;
struct thread {TYPE_1__ td_ru; int /*<<< orphan*/  td_proc; } ;
struct buf {int b_flags; void (* b_ckhashcalc ) (struct buf*) ;int /*<<< orphan*/  b_blkno; int /*<<< orphan*/  b_iooffset; struct ucred* b_rcred; int /*<<< orphan*/  b_ioflags; int /*<<< orphan*/  b_iocmd; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  BIO_READ ; 
 int B_CACHE ; 
 int B_CKHASH ; 
 int B_INVAL ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct vnode*,int /*<<< orphan*/ ,int) ; 
 int GB_CKHASH ; 
 int GB_NOSPARSE ; 
 int /*<<< orphan*/  KTR_BUF ; 
 struct ucred* NOCRED ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  breada (struct vnode*,int /*<<< orphan*/ *,int*,int,struct ucred*,int,void (*) (struct buf*)) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  bstrategy (struct buf*) ; 
 int bufwait (struct buf*) ; 
 struct ucred* crhold (struct ucred*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  dbtob (int /*<<< orphan*/ ) ; 
 int getblkx (struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct buf**) ; 
 int /*<<< orphan*/  racct_add_buf (int /*<<< orphan*/ ,struct buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  vfs_busy_pages (struct buf*,int /*<<< orphan*/ ) ; 

int
breadn_flags(struct vnode *vp, daddr_t blkno, int size, daddr_t *rablkno,
    int *rabsize, int cnt, struct ucred *cred, int flags,
    void (*ckhashfunc)(struct buf *), struct buf **bpp)
{
	struct buf *bp;
	struct thread *td;
	int error, readwait, rv;

	CTR3(KTR_BUF, "breadn(%p, %jd, %d)", vp, blkno, size);
	td = curthread;
	/*
	 * Can only return NULL if GB_LOCK_NOWAIT or GB_SPARSE flags
	 * are specified.
	 */
	error = getblkx(vp, blkno, size, 0, 0, flags, &bp);
	if (error != 0) {
		*bpp = NULL;
		return (error);
	}
	flags &= ~GB_NOSPARSE;
	*bpp = bp;

	/*
	 * If not found in cache, do some I/O
	 */
	readwait = 0;
	if ((bp->b_flags & B_CACHE) == 0) {
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(td->td_proc);
			racct_add_buf(td->td_proc, bp, 0);
			PROC_UNLOCK(td->td_proc);
		}
#endif /* RACCT */
		td->td_ru.ru_inblock++;
		bp->b_iocmd = BIO_READ;
		bp->b_flags &= ~B_INVAL;
		if ((flags & GB_CKHASH) != 0) {
			bp->b_flags |= B_CKHASH;
			bp->b_ckhashcalc = ckhashfunc;
		}
		bp->b_ioflags &= ~BIO_ERROR;
		if (bp->b_rcred == NOCRED && cred != NOCRED)
			bp->b_rcred = crhold(cred);
		vfs_busy_pages(bp, 0);
		bp->b_iooffset = dbtob(bp->b_blkno);
		bstrategy(bp);
		++readwait;
	}

	/*
	 * Attempt to initiate asynchronous I/O on read-ahead blocks.
	 */
	breada(vp, rablkno, rabsize, cnt, cred, flags, ckhashfunc);

	rv = 0;
	if (readwait) {
		rv = bufwait(bp);
		if (rv != 0) {
			brelse(bp);
			*bpp = NULL;
		}
	}
	return (rv);
}