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
typedef  scalar_t__ uint32_t ;
struct bbr_sendmap {int r_flags; scalar_t__ r_end; scalar_t__ r_start; } ;

/* Variables and functions */
 int BBR_ACKED ; 
 scalar_t__ SEQ_GT (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LT (scalar_t__,scalar_t__) ; 
 struct bbr_sendmap* TAILQ_NEXT (struct bbr_sendmap*,int /*<<< orphan*/ ) ; 
 struct bbr_sendmap* TAILQ_PREV (struct bbr_sendmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_head ; 
 int /*<<< orphan*/  r_next ; 

__attribute__((used)) static int
bbr_sack_mergable(struct bbr_sendmap *at,
		  uint32_t start, uint32_t end)
{
	/* 
	 * Given a sack block defined by
	 * start and end, and a current postion
	 * at. Return 1 if either side of at
	 * would show that the block is mergable
	 * to that side. A block to be mergable
	 * must have overlap with the start/end
	 * and be in the SACK'd state.
	 */
	struct bbr_sendmap *l_rsm;
	struct bbr_sendmap *r_rsm;

	/* first get the either side blocks */
	l_rsm = TAILQ_PREV(at, bbr_head, r_next);
	r_rsm = TAILQ_NEXT(at, r_next);
	if (l_rsm && (l_rsm->r_flags & BBR_ACKED)) {
		/* Potentially mergeable */
		if ((l_rsm->r_end == start) ||
		    (SEQ_LT(start, l_rsm->r_end) &&
		     SEQ_GT(end, l_rsm->r_end))) {
			    /*
			     * map blk   |------|
			     * sack blk         |------|
			     * <or>
			     * map blk   |------|
			     * sack blk      |------|
			     */
			    return (1);
		    }
	}
	if (r_rsm && (r_rsm->r_flags & BBR_ACKED)) {
		/* Potentially mergeable */
		if ((r_rsm->r_start == end) ||
		    (SEQ_LT(start, r_rsm->r_start) &&
		     SEQ_GT(end, r_rsm->r_start))) {
			/* 
			 * map blk          |---------|
			 * sack blk    |----|
			 * <or>
			 * map blk          |---------|
			 * sack blk    |-------|
			 */
			return (1);
		}
	}
	return (0);
}