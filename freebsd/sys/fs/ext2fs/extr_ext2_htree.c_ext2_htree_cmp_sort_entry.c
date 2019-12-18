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
struct ext2fs_htree_sort_entry {scalar_t__ h_hash; } ;

/* Variables and functions */

__attribute__((used)) static int
ext2_htree_cmp_sort_entry(const void *e1, const void *e2)
{
	const struct ext2fs_htree_sort_entry *entry1, *entry2;

	entry1 = (const struct ext2fs_htree_sort_entry *)e1;
	entry2 = (const struct ext2fs_htree_sort_entry *)e2;

	if (entry1->h_hash < entry2->h_hash)
		return (-1);
	if (entry1->h_hash > entry2->h_hash)
		return (1);
	return (0);
}