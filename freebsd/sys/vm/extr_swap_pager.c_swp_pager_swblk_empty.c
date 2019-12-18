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
struct swblk {scalar_t__* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ SWAPBLK_NONE ; 
 int SWAP_META_PAGES ; 

__attribute__((used)) static bool
swp_pager_swblk_empty(struct swblk *sb, int start, int limit)
{
	int i;

	MPASS(0 <= start && start <= limit && limit <= SWAP_META_PAGES);
	for (i = start; i < limit; i++) {
		if (sb->d[i] != SWAPBLK_NONE)
			return (false);
	}
	return (true);
}