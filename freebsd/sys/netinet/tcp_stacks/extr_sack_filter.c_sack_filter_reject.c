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
struct sackblk {scalar_t__ end; scalar_t__ start; } ;
struct sack_filter {int /*<<< orphan*/  sf_used; void* sf_bits; TYPE_1__* sf_blks; } ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int SACK_FILTER_BLOCKS ; 
 scalar_t__ SEQ_GT (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LT (scalar_t__,scalar_t__) ; 
 void* sack_blk_clr (struct sack_filter*,int) ; 
 scalar_t__ sack_blk_used (struct sack_filter*,int) ; 

void
sack_filter_reject(struct sack_filter *sf, struct sackblk *in)
{
	/* 
	 * Given a specified block (that had made
	 * it past the sack filter). Reject that
	 * block triming it off any sack-filter block
	 * that has it. Usually because the block was
	 * too small and did not cover a whole send.
	 *
	 * This function will only "undo" sack-blocks 
	 * that are fresh and touch the edges of 
	 * blocks in our filter.
	 */
	int i;

	for(i=0; i<SACK_FILTER_BLOCKS; i++) {
		if (sack_blk_used(sf, i) == 0)
			continue;
		/* 
		 * Now given the sack-filter block does it touch
		 * with one of the ends 
		 */
		if (sf->sf_blks[i].end == in->end) {
			/* The end moves back to start */
			if (SEQ_GT(in->start, sf->sf_blks[i].start))
				/* in-blk       |----| */
				/* sf-blk  |---------| */
				sf->sf_blks[i].end = in->start;
			else {
				/* It consumes this block */
				/* in-blk  |---------| */
				/* sf-blk     |------| */
				/* <or> */
				/* sf-blk  |---------| */
				sf->sf_bits = sack_blk_clr(sf, i);
				sf->sf_used--;
			}
			continue;
		}
		if (sf->sf_blks[i].start == in->start) {
			if (SEQ_LT(in->end, sf->sf_blks[i].end)) {
				/* in-blk  |----|      */
				/* sf-blk  |---------| */
				sf->sf_blks[i].start = in->end;
			} else {
				/* It consumes this block */
				/* in-blk  |----------|  */
				/* sf-blk  |-------|     */
				/* <or> */
				/* sf-blk  |----------|  */
				sf->sf_bits = sack_blk_clr(sf, i);
				sf->sf_used--;
			}
			continue;
		}
	}
}