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
typedef  int /*<<< orphan*/  uint32_t ;
struct ext2fs_htree_lookup_level {scalar_t__ h_entries; struct ext2fs_htree_entry* h_entry; } ;
struct ext2fs_htree_entry {int dummy; } ;

/* Variables and functions */
 int ext2_htree_get_count (scalar_t__) ; 
 int /*<<< orphan*/  ext2_htree_set_block (struct ext2fs_htree_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_htree_set_count (scalar_t__,int) ; 
 int /*<<< orphan*/  ext2_htree_set_hash (struct ext2fs_htree_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ext2fs_htree_entry*,struct ext2fs_htree_entry*,int) ; 

__attribute__((used)) static void
ext2_htree_insert_entry_to_level(struct ext2fs_htree_lookup_level *level,
    uint32_t hash, uint32_t blk)
{
	struct ext2fs_htree_entry *target;
	int entries_num;

	target = level->h_entry + 1;
	entries_num = ext2_htree_get_count(level->h_entries);

	memmove(target + 1, target, (char *)(level->h_entries + entries_num) -
	    (char *)target);
	ext2_htree_set_block(target, blk);
	ext2_htree_set_hash(target, hash);
	ext2_htree_set_count(level->h_entries, entries_num + 1);
}