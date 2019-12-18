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
typedef  int uint32_t ;
struct sackblk {int dummy; } ;
struct sack_filter {int /*<<< orphan*/  sf_bits; int /*<<< orphan*/ * sf_blks; } ;
typedef  int int32_t ;

/* Variables and functions */
 int SACK_FILTER_BLOCKS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sack_blk_clr (struct sack_filter*,int) ; 
 int /*<<< orphan*/  sack_blk_set (struct sack_filter*,int) ; 
 scalar_t__ sack_blk_used (struct sack_filter*,int) ; 

__attribute__((used)) static void
sack_move_to_empty(struct sack_filter *sf, uint32_t idx)
{
	int32_t i, cnt;

	i = (idx + 1) % SACK_FILTER_BLOCKS;
	for (cnt=0; cnt <(SACK_FILTER_BLOCKS-1); cnt++) {
		if (sack_blk_used(sf, i) == 0) {
			memcpy(&sf->sf_blks[i], &sf->sf_blks[idx], sizeof(struct sackblk));			
			sf->sf_bits = sack_blk_clr(sf, idx);
			sf->sf_bits = sack_blk_set(sf, i);
			return;
		}
		i++;
		i %= SACK_FILTER_BLOCKS;
	}
}