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
struct sackblk {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct sack_filter {int sf_cur; TYPE_1__* sf_blks; int /*<<< orphan*/  sf_ack; } ;
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int SACK_FILTER_BLOCKS ; 
 scalar_t__ SEQ_GEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_LEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sack_blk_used (struct sack_filter*,int) ; 

__attribute__((used)) static int32_t
is_sack_on_board(struct sack_filter *sf, struct sackblk *b)
{
	int32_t i, cnt;

	for (i = sf->sf_cur, cnt=0; cnt < SACK_FILTER_BLOCKS; cnt++) {
		if (sack_blk_used(sf, i)) {
			if (SEQ_LT(b->start, sf->sf_ack)) {
				/* Behind cum-ack update */
				b->start = sf->sf_ack;
			}
			if (SEQ_LT(b->end, sf->sf_ack)) {
				/* End back behind too */
				b->end = sf->sf_ack;
			}
			if (b->start == b->end) {
				return(1);
			}
			/* Jonathans Rule 1 */
			if (SEQ_LEQ(sf->sf_blks[i].start, b->start) &&
			    SEQ_GEQ(sf->sf_blks[i].end, b->end)) {
				/**
				 * Our board has this entirely in
				 * whole or in part:
				 *
				 * board  |-------------|
				 * sack   |-------------|
				 * <or>
				 * board  |-------------|
				 * sack       |----|
				 *
				 */
				return(1);
			}
			/* Jonathans Rule 2 */
			if(SEQ_LT(sf->sf_blks[i].end, b->start)) {
				/**
				 * Not near each other:
				 * 
				 * board   |---|
				 * sack           |---|
				 */
				goto nxt_blk;
			}
			/* Jonathans Rule 3 */
			if (SEQ_GT(sf->sf_blks[i].start, b->end)) {
				/**
				 * Not near each other:
				 * 
				 * board         |---|
				 * sack  |---|
				 */
				goto nxt_blk;
			}
			if (SEQ_LEQ(sf->sf_blks[i].start, b->start)) {
				/** 
				 * The board block partial meets:
				 *
				 *  board   |--------|
				 *  sack        |----------|  
				 *    <or>
				 *  board   |--------|
				 *  sack    |--------------|  
				 *
				 * up with this one (we have part of it).
				 * 1) Update the board block to the new end
				 *      and
				 * 2) Update the start of this block to my end.
				 */
				b->start = sf->sf_blks[i].end;
				sf->sf_blks[i].end = b->end;
				goto nxt_blk;
			}
			if (SEQ_GEQ(sf->sf_blks[i].end, b->end)) {
				/** 
				 * The board block partial meets:
				 *
				 *  board       |--------|
				 *  sack  |----------|  
				 *     <or>
				 *  board       |----|
				 *  sack  |----------|  
				 * 1) Update the board block to the new start
				 *      and
				 * 2) Update the start of this block to my end.
				 */
				b->end = sf->sf_blks[i].start;
				sf->sf_blks[i].start = b->start;
				goto nxt_blk;
			}
		} 
	nxt_blk:
		i++;
		i %= SACK_FILTER_BLOCKS;
	}
	/* Did we totally consume it in pieces? */
	if (b->start != b->end)
		return(0);
	else
		return(1);
}