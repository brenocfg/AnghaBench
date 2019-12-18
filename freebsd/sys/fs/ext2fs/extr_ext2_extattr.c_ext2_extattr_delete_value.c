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
typedef  int uint16_t ;
struct ext2fs_extattr_entry {int e_value_offs; scalar_t__ e_value_size; } ;

/* Variables and functions */
 struct ext2fs_extattr_entry* EXT2_EXTATTR_NEXT (struct ext2fs_extattr_entry*) ; 
 int EXT2_EXTATTR_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  EXT2_IS_LAST_ENTRY (struct ext2fs_extattr_entry*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static uint16_t
ext2_extattr_delete_value(char *off,
    struct ext2fs_extattr_entry *first_entry,
    struct ext2fs_extattr_entry *entry, char *end)
{
	uint16_t min_offs;
	struct ext2fs_extattr_entry *next;

	min_offs = end - off;
	next = first_entry;
	while (!EXT2_IS_LAST_ENTRY(next)) {
		if (min_offs > next->e_value_offs && next->e_value_offs > 0)
			min_offs = next->e_value_offs;

		next = EXT2_EXTATTR_NEXT(next);
	}

	if (entry->e_value_size == 0)
		return (min_offs);

	memmove(off + min_offs + EXT2_EXTATTR_SIZE(entry->e_value_size),
	    off + min_offs, entry->e_value_offs - min_offs);

	/* Adjust all value offsets */
	next = first_entry;
	while (!EXT2_IS_LAST_ENTRY(next))
	{
		if (next->e_value_offs > 0 &&
		    next->e_value_offs < entry->e_value_offs)
			next->e_value_offs +=
			    EXT2_EXTATTR_SIZE(entry->e_value_size);

		next = EXT2_EXTATTR_NEXT(next);
	}

	min_offs += EXT2_EXTATTR_SIZE(entry->e_value_size);

	return (min_offs);
}