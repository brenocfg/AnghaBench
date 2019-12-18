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
struct vnode {int v_type; } ;
struct bufv {scalar_t__ bv_cnt; int /*<<< orphan*/  bv_hd; } ;
struct bufobj {int bo_flag; struct bufv bo_dirty; struct bufv bo_clean; } ;
struct buf {int b_flags; int b_xflags; struct bufobj* b_bufobj; struct vnode* b_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int BO_ONWORKLST ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int BX_VNCLEAN ; 
 int BX_VNDIRTY ; 
 int B_DELWRI ; 
 int B_PAGING ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct buf*,struct vnode*,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_BUF ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bufobj*,int /*<<< orphan*/ ) ; 
 struct buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct buf* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  VCHR 129 
#define  VDIR 128 
 int /*<<< orphan*/  bo_synclist ; 
 int /*<<< orphan*/  buf_vlist_add (struct buf*,struct bufobj*,int) ; 
 int /*<<< orphan*/  buf_vlist_remove (struct buf*) ; 
 int /*<<< orphan*/  buflists ; 
 int dirdelay ; 
 int filedelay ; 
 int metadelay ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  reassignbufcalls ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  syncer_worklist_len ; 
 int /*<<< orphan*/  vn_syncer_add_to_worklist (struct bufobj*,int) ; 

void
reassignbuf(struct buf *bp)
{
	struct vnode *vp;
	struct bufobj *bo;
	int delay;
#ifdef INVARIANTS
	struct bufv *bv;
#endif

	vp = bp->b_vp;
	bo = bp->b_bufobj;
	++reassignbufcalls;

	CTR3(KTR_BUF, "reassignbuf(%p) vp %p flags %X",
	    bp, bp->b_vp, bp->b_flags);
	/*
	 * B_PAGING flagged buffers cannot be reassigned because their vp
	 * is not fully linked in.
	 */
	if (bp->b_flags & B_PAGING)
		panic("cannot reassign paging buffer");

	/*
	 * Delete from old vnode list, if on one.
	 */
	BO_LOCK(bo);
	if (bp->b_xflags & (BX_VNDIRTY | BX_VNCLEAN))
		buf_vlist_remove(bp);
	else
		panic("reassignbuf: Buffer %p not on queue.", bp);
	/*
	 * If dirty, put on list of dirty buffers; otherwise insert onto list
	 * of clean buffers.
	 */
	if (bp->b_flags & B_DELWRI) {
		if ((bo->bo_flag & BO_ONWORKLST) == 0) {
			switch (vp->v_type) {
			case VDIR:
				delay = dirdelay;
				break;
			case VCHR:
				delay = metadelay;
				break;
			default:
				delay = filedelay;
			}
			vn_syncer_add_to_worklist(bo, delay);
		}
		buf_vlist_add(bp, bo, BX_VNDIRTY);
	} else {
		buf_vlist_add(bp, bo, BX_VNCLEAN);

		if ((bo->bo_flag & BO_ONWORKLST) && bo->bo_dirty.bv_cnt == 0) {
			mtx_lock(&sync_mtx);
			LIST_REMOVE(bo, bo_synclist);
			syncer_worklist_len--;
			mtx_unlock(&sync_mtx);
			bo->bo_flag &= ~BO_ONWORKLST;
		}
	}
#ifdef INVARIANTS
	bv = &bo->bo_clean;
	bp = TAILQ_FIRST(&bv->bv_hd);
	KASSERT(bp == NULL || bp->b_bufobj == bo,
	    ("bp %p wrong b_bufobj %p should be %p", bp, bp->b_bufobj, bo));
	bp = TAILQ_LAST(&bv->bv_hd, buflists);
	KASSERT(bp == NULL || bp->b_bufobj == bo,
	    ("bp %p wrong b_bufobj %p should be %p", bp, bp->b_bufobj, bo));
	bv = &bo->bo_dirty;
	bp = TAILQ_FIRST(&bv->bv_hd);
	KASSERT(bp == NULL || bp->b_bufobj == bo,
	    ("bp %p wrong b_bufobj %p should be %p", bp, bp->b_bufobj, bo));
	bp = TAILQ_LAST(&bv->bv_hd, buflists);
	KASSERT(bp == NULL || bp->b_bufobj == bo,
	    ("bp %p wrong b_bufobj %p should be %p", bp, bp->b_bufobj, bo));
#endif
	BO_UNLOCK(bo);
}