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
typedef  int /*<<< orphan*/  tcp_seq ;
struct sackblk {int dummy; } ;
struct sack_filter {size_t sf_cur; size_t sf_used; int /*<<< orphan*/  sf_bits; struct sackblk* sf_blks; } ;
typedef  int int32_t ;

/* Variables and functions */
 size_t SACK_FILTER_BLOCKS ; 
 int TCP_MAX_SACK ; 
 int /*<<< orphan*/  empty_avail ; 
 size_t highest_used ; 
 scalar_t__ is_sack_on_board (struct sack_filter*,struct sackblk*) ; 
 int /*<<< orphan*/  memcpy (struct sackblk*,struct sackblk*,int) ; 
 int /*<<< orphan*/  over_written ; 
 int /*<<< orphan*/  sack_blk_set (struct sack_filter*,size_t) ; 
 scalar_t__ sack_blk_used (struct sack_filter*,size_t) ; 
 int /*<<< orphan*/  sack_move_to_empty (struct sack_filter*,size_t) ; 

__attribute__((used)) static int32_t
sack_filter_new(struct sack_filter *sf, struct sackblk *in, int numblks, tcp_seq th_ack)
{
	struct sackblk blkboard[TCP_MAX_SACK];
	int32_t num, i;
	/* 
	 * First lets trim the old and possibly 
	 * throw any away we have. 
	 */
	for(i=0, num=0; i<numblks; i++) {
		if (is_sack_on_board(sf, &in[i]))
			continue;
		memcpy(&blkboard[num], &in[i], sizeof(struct sackblk));
		num++;
	}
	if (num == 0)
		return(num);

	/* Now what we are left with is either 
	 * completely merged on to the board
	 * from the above steps, or is new
	 * and need to be added to the board
	 * with the last one updated to current.
	 *
	 * First copy it out, we want to return that
	 * to our caller for processing.
	 */
	memcpy(in, blkboard, (num * sizeof(struct sackblk)));	
	numblks = num;
	/* Now go through and add to our board as needed */
	for(i=(num-1); i>=0; i--) {
		if (is_sack_on_board(sf, &blkboard[i])) {
			continue;
		}
		/* Add this guy its not listed */
		sf->sf_cur++;
		sf->sf_cur %= SACK_FILTER_BLOCKS;
		if ((sack_blk_used(sf, sf->sf_cur)) &&
		    (sf->sf_used < SACK_FILTER_BLOCKS)) {
			sack_move_to_empty(sf, sf->sf_cur);
		}
#ifndef _KERNEL
		if (sack_blk_used(sf, sf->sf_cur)) {
			over_written++;
			if (sf->sf_used < SACK_FILTER_BLOCKS)
				empty_avail++;
		}
#endif
		memcpy(&sf->sf_blks[sf->sf_cur], &in[i], sizeof(struct sackblk));
		if (sack_blk_used(sf, sf->sf_cur) == 0) {
			sf->sf_used++;
#ifndef _KERNEL
			if (sf->sf_used > highest_used)
				highest_used = sf->sf_used;
#endif
			sf->sf_bits = sack_blk_set(sf, sf->sf_cur);
		}
	}
	return(numblks);
}