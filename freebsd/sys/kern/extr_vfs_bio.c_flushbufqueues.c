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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct bufqueue {int /*<<< orphan*/  bq_queue; } ;
struct bufdomain {struct bufqueue bd_dirtyq; } ;
struct buf {scalar_t__ b_qindex; int b_vflags; int b_flags; struct vnode* b_vp; int /*<<< orphan*/  b_dep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  BQ_LOCK (struct bufqueue*) ; 
 int /*<<< orphan*/  BQ_UNLOCK (struct bufqueue*) ; 
 int BUF_LOCK (struct buf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 int BV_BKGRDINPROG ; 
 int B_DELWRI ; 
 int B_INVAL ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct buf*,struct vnode*,int) ; 
 int /*<<< orphan*/  KTR_BUF ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 int LK_TRYUPGRADE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ QUEUE_SENTINEL ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 struct buf* TAILQ_NEXT (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_NOWAIT ; 
 int /*<<< orphan*/  b_freelist ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  bremfree (struct buf*) ; 
 int /*<<< orphan*/  bremfreef (struct buf*) ; 
 scalar_t__ buf_countdeps (struct buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ bufdaemonproc ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 scalar_t__ curproc ; 
 int flushwithdeps ; 
 int /*<<< orphan*/  free (struct buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ hirunningspace ; 
 struct buf* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  maybe_yield () ; 
 int /*<<< orphan*/  notbufdflushes ; 
 scalar_t__ runningbufspace ; 
 int /*<<< orphan*/  vfs_bio_awrite (struct buf*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_lock (struct vnode*,int) ; 
 scalar_t__ vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitrunningbufspace () ; 

__attribute__((used)) static int
flushbufqueues(struct vnode *lvp, struct bufdomain *bd, int target,
    int flushdeps)
{
	struct bufqueue *bq;
	struct buf *sentinel;
	struct vnode *vp;
	struct mount *mp;
	struct buf *bp;
	int hasdeps;
	int flushed;
	int error;
	bool unlock;

	flushed = 0;
	bq = &bd->bd_dirtyq;
	bp = NULL;
	sentinel = malloc(sizeof(struct buf), M_TEMP, M_WAITOK | M_ZERO);
	sentinel->b_qindex = QUEUE_SENTINEL;
	BQ_LOCK(bq);
	TAILQ_INSERT_HEAD(&bq->bq_queue, sentinel, b_freelist);
	BQ_UNLOCK(bq);
	while (flushed != target) {
		maybe_yield();
		BQ_LOCK(bq);
		bp = TAILQ_NEXT(sentinel, b_freelist);
		if (bp != NULL) {
			TAILQ_REMOVE(&bq->bq_queue, sentinel, b_freelist);
			TAILQ_INSERT_AFTER(&bq->bq_queue, bp, sentinel,
			    b_freelist);
		} else {
			BQ_UNLOCK(bq);
			break;
		}
		/*
		 * Skip sentinels inserted by other invocations of the
		 * flushbufqueues(), taking care to not reorder them.
		 *
		 * Only flush the buffers that belong to the
		 * vnode locked by the curthread.
		 */
		if (bp->b_qindex == QUEUE_SENTINEL || (lvp != NULL &&
		    bp->b_vp != lvp)) {
			BQ_UNLOCK(bq);
			continue;
		}
		error = BUF_LOCK(bp, LK_EXCLUSIVE | LK_NOWAIT, NULL);
		BQ_UNLOCK(bq);
		if (error != 0)
			continue;

		/*
		 * BKGRDINPROG can only be set with the buf and bufobj
		 * locks both held.  We tolerate a race to clear it here.
		 */
		if ((bp->b_vflags & BV_BKGRDINPROG) != 0 ||
		    (bp->b_flags & B_DELWRI) == 0) {
			BUF_UNLOCK(bp);
			continue;
		}
		if (bp->b_flags & B_INVAL) {
			bremfreef(bp);
			brelse(bp);
			flushed++;
			continue;
		}

		if (!LIST_EMPTY(&bp->b_dep) && buf_countdeps(bp, 0)) {
			if (flushdeps == 0) {
				BUF_UNLOCK(bp);
				continue;
			}
			hasdeps = 1;
		} else
			hasdeps = 0;
		/*
		 * We must hold the lock on a vnode before writing
		 * one of its buffers. Otherwise we may confuse, or
		 * in the case of a snapshot vnode, deadlock the
		 * system.
		 *
		 * The lock order here is the reverse of the normal
		 * of vnode followed by buf lock.  This is ok because
		 * the NOWAIT will prevent deadlock.
		 */
		vp = bp->b_vp;
		if (vn_start_write(vp, &mp, V_NOWAIT) != 0) {
			BUF_UNLOCK(bp);
			continue;
		}
		if (lvp == NULL) {
			unlock = true;
			error = vn_lock(vp, LK_EXCLUSIVE | LK_NOWAIT);
		} else {
			ASSERT_VOP_LOCKED(vp, "getbuf");
			unlock = false;
			error = VOP_ISLOCKED(vp) == LK_EXCLUSIVE ? 0 :
			    vn_lock(vp, LK_TRYUPGRADE);
		}
		if (error == 0) {
			CTR3(KTR_BUF, "flushbufqueue(%p) vp %p flags %X",
			    bp, bp->b_vp, bp->b_flags);
			if (curproc == bufdaemonproc) {
				vfs_bio_awrite(bp);
			} else {
				bremfree(bp);
				bwrite(bp);
				counter_u64_add(notbufdflushes, 1);
			}
			vn_finished_write(mp);
			if (unlock)
				VOP_UNLOCK(vp, 0);
			flushwithdeps += hasdeps;
			flushed++;

			/*
			 * Sleeping on runningbufspace while holding
			 * vnode lock leads to deadlock.
			 */
			if (curproc == bufdaemonproc &&
			    runningbufspace > hirunningspace)
				waitrunningbufspace();
			continue;
		}
		vn_finished_write(mp);
		BUF_UNLOCK(bp);
	}
	BQ_LOCK(bq);
	TAILQ_REMOVE(&bq->bq_queue, sentinel, b_freelist);
	BQ_UNLOCK(bq);
	free(sentinel, M_TEMP);
	return (flushed);
}