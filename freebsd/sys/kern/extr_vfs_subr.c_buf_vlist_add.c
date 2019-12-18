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
struct bufv {scalar_t__ bv_cnt; int /*<<< orphan*/  bv_root; int /*<<< orphan*/  bv_hd; } ;
struct bufobj {int bo_flag; struct bufv bo_clean; struct bufv bo_dirty; } ;
struct buf {int b_xflags; int /*<<< orphan*/  b_lblkno; } ;
typedef  int b_xflags_t ;
struct TYPE_2__ {int /*<<< orphan*/  b_lblkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BO_WLOCKED (struct bufobj*) ; 
 int BO_DEAD ; 
 int BUF_PCTRIE_INSERT (int /*<<< orphan*/ *,struct buf*) ; 
 struct buf* BUF_PCTRIE_LOOKUP_LE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int BX_VNCLEAN ; 
 int BX_VNDIRTY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_bobufs ; 
 int /*<<< orphan*/  buflists ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
buf_vlist_add(struct buf *bp, struct bufobj *bo, b_xflags_t xflags)
{
	struct bufv *bv;
	struct buf *n;
	int error;

	ASSERT_BO_WLOCKED(bo);
	KASSERT((xflags & BX_VNDIRTY) == 0 || (bo->bo_flag & BO_DEAD) == 0,
	    ("dead bo %p", bo));
	KASSERT((bp->b_xflags & (BX_VNDIRTY|BX_VNCLEAN)) == 0,
	    ("buf_vlist_add: Buf %p has existing xflags %d", bp, bp->b_xflags));
	bp->b_xflags |= xflags;
	if (xflags & BX_VNDIRTY)
		bv = &bo->bo_dirty;
	else
		bv = &bo->bo_clean;

	/*
	 * Keep the list ordered.  Optimize empty list insertion.  Assume
	 * we tend to grow at the tail so lookup_le should usually be cheaper
	 * than _ge. 
	 */
	if (bv->bv_cnt == 0 ||
	    bp->b_lblkno > TAILQ_LAST(&bv->bv_hd, buflists)->b_lblkno)
		TAILQ_INSERT_TAIL(&bv->bv_hd, bp, b_bobufs);
	else if ((n = BUF_PCTRIE_LOOKUP_LE(&bv->bv_root, bp->b_lblkno)) == NULL)
		TAILQ_INSERT_HEAD(&bv->bv_hd, bp, b_bobufs);
	else
		TAILQ_INSERT_AFTER(&bv->bv_hd, n, bp, b_bobufs);
	error = BUF_PCTRIE_INSERT(&bv->bv_root, bp);
	if (error)
		panic("buf_vlist_add:  Preallocated nodes insufficient.");
	bv->bv_cnt++;
}