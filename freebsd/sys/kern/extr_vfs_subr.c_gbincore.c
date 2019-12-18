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
struct TYPE_4__ {int /*<<< orphan*/  bv_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  bv_root; } ;
struct bufobj {TYPE_2__ bo_dirty; TYPE_1__ bo_clean; } ;
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BO_LOCKED (struct bufobj*) ; 
 struct buf* BUF_PCTRIE_LOOKUP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct buf *
gbincore(struct bufobj *bo, daddr_t lblkno)
{
	struct buf *bp;

	ASSERT_BO_LOCKED(bo);
	bp = BUF_PCTRIE_LOOKUP(&bo->bo_clean.bv_root, lblkno);
	if (bp != NULL)
		return (bp);
	return BUF_PCTRIE_LOOKUP(&bo->bo_dirty.bv_root, lblkno);
}