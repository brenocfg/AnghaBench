#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_daddr_t ;
struct sbuf {int dummy; } ;
struct gap_stats {int dummy; } ;
typedef  size_t daddr_t ;
typedef  TYPE_2__* blist_t ;
struct TYPE_5__ {size_t bl_radix; size_t bl_blocks; TYPE_1__* bl_root; } ;
struct TYPE_4__ {scalar_t__ bm_bitmap; } ;

/* Variables and functions */
 size_t BLIST_BMAP_RADIX ; 
 size_t BLIST_META_MASK ; 
 size_t BLIST_META_RADIX ; 
 int bitpos (int) ; 
 int bitrange (int,int) ; 
 int /*<<< orphan*/  dump_gap_stats (struct gap_stats*,struct sbuf*) ; 
 scalar_t__ gap_stats_counting (struct gap_stats*) ; 
 int /*<<< orphan*/  init_gap_stats (struct gap_stats*) ; 
 scalar_t__ radix_to_skip (size_t) ; 
 int /*<<< orphan*/  update_gap_stats (struct gap_stats*,size_t) ; 

void
blist_stats(blist_t bl, struct sbuf *s)
{
	struct gap_stats gstats;
	struct gap_stats *stats = &gstats;
	daddr_t i, nodes, radix;
	u_daddr_t diff, mask;
	int digit;

	init_gap_stats(stats);
	nodes = 0;
	i = bl->bl_radix;
	while (i < bl->bl_radix + bl->bl_blocks) {
		/*
		 * Find max size subtree starting at i.
		 */
		radix = BLIST_BMAP_RADIX;
		while (((i / radix) & BLIST_META_MASK) == 0)
			radix *= BLIST_META_RADIX;

		/*
		 * Check for skippable subtrees starting at i.
		 */
		while (radix > BLIST_BMAP_RADIX) {
			if (bl->bl_root[nodes].bm_bitmap == 0) {
				if (gap_stats_counting(stats))
					update_gap_stats(stats, i);
				break;
			}

			/*
			 * Skip subtree root.
			 */
			nodes++;
			radix /= BLIST_META_RADIX;
		}
		if (radix == BLIST_BMAP_RADIX) {
			/*
			 * Scan leaf.
			 */
			mask = bl->bl_root[nodes].bm_bitmap;
			diff = mask ^ (mask << 1);
			if (gap_stats_counting(stats))
				diff ^= 1;
			while (diff != 0) {
				digit = bitpos(diff);
				update_gap_stats(stats, i + digit);
				diff ^= bitrange(digit, 1);
			}
		}
		nodes += radix_to_skip(radix);
		i += radix;
	}
	update_gap_stats(stats, i);
	dump_gap_stats(stats, s);
}