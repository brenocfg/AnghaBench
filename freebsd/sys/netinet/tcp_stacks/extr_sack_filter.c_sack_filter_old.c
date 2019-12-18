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
struct sackblk {int dummy; } ;
struct sack_filter {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int TCP_MAX_SACK ; 
 int /*<<< orphan*/  cnt_skipped_oldsack ; 
 int /*<<< orphan*/  cnt_used_oldsack ; 
 scalar_t__ is_sack_on_board (struct sack_filter*,struct sackblk*) ; 
 int /*<<< orphan*/  memcpy (struct sackblk*,struct sackblk*,int) ; 

__attribute__((used)) static int32_t
sack_filter_old(struct sack_filter *sf, struct sackblk *in, int  numblks)
{
	int32_t num, i;
	struct sackblk blkboard[TCP_MAX_SACK];
	/* 
	 * An old sack has arrived. It may contain data
	 * we do not have. We might not have it since
	 * we could have had a lost ack <or> we might have the
	 * entire thing on our current board. We want to prune
	 * off anything we have. With this function though we
	 * won't add to the board.
	 */
	for( i = 0, num = 0; i<numblks; i++ ) {
		if (is_sack_on_board(sf, &in[i])) {
#ifndef _KERNEL
			cnt_skipped_oldsack++;
#endif
			continue;
		}
		/* Did not find it (or found only 
		 * a piece of it). Copy it to 
		 * our outgoing board.
		 */
		memcpy(&blkboard[num], &in[i], sizeof(struct sackblk));
#ifndef _KERNEL
		cnt_used_oldsack++;
#endif
		num++;
	}
	if (num) {
		memcpy(in, blkboard, (num * sizeof(struct sackblk)));
	}
	return (num);
}