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
typedef  size_t u_int ;
struct ext2fs_htree_lookup_info {size_t h_levels_num; TYPE_1__* h_levels; } ;
struct buf {int dummy; } ;
struct TYPE_2__ {struct buf* h_bp; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buf*) ; 

__attribute__((used)) static void
ext2_htree_release(struct ext2fs_htree_lookup_info *info)
{
	u_int i;

	for (i = 0; i < info->h_levels_num; i++) {
		struct buf *bp = info->h_levels[i].h_bp;

		if (bp != NULL)
			brelse(bp);
	}
}