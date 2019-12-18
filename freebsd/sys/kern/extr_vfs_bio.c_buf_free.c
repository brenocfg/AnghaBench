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
struct buf {int b_flags; int b_vflags; scalar_t__ b_rcred; scalar_t__ b_wcred; int /*<<< orphan*/  b_dep; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_freebuffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 int BV_BKGRDINPROG ; 
 int B_REMFREE ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ NOCRED ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bremfreef (struct buf*) ; 
 int /*<<< orphan*/  buf_deallocate (struct buf*) ; 
 int /*<<< orphan*/  buf_zone ; 
 TYPE_1__* bufdomain (struct buf*) ; 
 int /*<<< orphan*/  bufkva_free (struct buf*) ; 
 int /*<<< orphan*/  crfree (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct buf*) ; 

__attribute__((used)) static void
buf_free(struct buf *bp)
{

	if (bp->b_flags & B_REMFREE)
		bremfreef(bp);
	if (bp->b_vflags & BV_BKGRDINPROG)
		panic("losing buffer 1");
	if (bp->b_rcred != NOCRED) {
		crfree(bp->b_rcred);
		bp->b_rcred = NOCRED;
	}
	if (bp->b_wcred != NOCRED) {
		crfree(bp->b_wcred);
		bp->b_wcred = NOCRED;
	}
	if (!LIST_EMPTY(&bp->b_dep))
		buf_deallocate(bp);
	bufkva_free(bp);
	atomic_add_int(&bufdomain(bp)->bd_freebuffers, 1);
	BUF_UNLOCK(bp);
	uma_zfree(buf_zone, bp);
}