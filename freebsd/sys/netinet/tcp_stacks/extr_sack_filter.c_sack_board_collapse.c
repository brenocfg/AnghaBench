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
struct sack_filter {size_t sf_cur; int /*<<< orphan*/ * sf_blks; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 size_t SACK_FILTER_BLOCKS ; 
 scalar_t__ sack_blk_used (struct sack_filter*,size_t) ; 
 size_t sack_blocks_overlap_or_meet (struct sack_filter*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sack_collapse (struct sack_filter*,size_t,size_t) ; 

__attribute__((used)) static void
sack_board_collapse(struct sack_filter *sf)
{
	int32_t i, j, i_d, j_d;

	for(i=0; i<SACK_FILTER_BLOCKS; i++) {
		if (sack_blk_used(sf, i) == 0)
			continue;
		/*
		 * Look at all other blocks but this guy 
		 * to see if they overlap. If so we collapse
		 * the two blocks together.
		 */
		j = sack_blocks_overlap_or_meet(sf, &sf->sf_blks[i], i);
		if (j == -1) {
			/* No overlap */
			continue;
		}
		/* 
		 * Ok j and i overlap with each other, collapse the
		 * one out furthest away from the current position.
		 */
		if (sf->sf_cur > i)
			i_d = sf->sf_cur - i;
		else
			i_d = i - sf->sf_cur;
		if (sf->sf_cur > j)
			j_d = sf->sf_cur - j;
		else
			j_d = j - sf->sf_cur;
		if (j_d > i_d) {
			sack_collapse(sf, j, i);
		} else
			sack_collapse(sf, i, j);
	}
}