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
struct ext2fs_extattr_entry {int /*<<< orphan*/  e_name_len; } ;

/* Variables and functions */
 int EXT2_EXTATTR_LEN (int /*<<< orphan*/ ) ; 
 struct ext2fs_extattr_entry* EXT2_EXTATTR_NEXT (struct ext2fs_extattr_entry*) ; 
 int /*<<< orphan*/  EXT2_IS_LAST_ENTRY (struct ext2fs_extattr_entry*) ; 
 int /*<<< orphan*/  ext2_extattr_delete_value (char*,struct ext2fs_extattr_entry*,struct ext2fs_extattr_entry*,char*) ; 
 int /*<<< orphan*/  memmove (struct ext2fs_extattr_entry*,char*,int) ; 

__attribute__((used)) static void
ext2_extattr_delete_entry(char *off,
    struct ext2fs_extattr_entry *first_entry,
    struct ext2fs_extattr_entry *entry, char *end)
{
	char *pad;
	struct ext2fs_extattr_entry *next;

	/* Clean entry value */
	ext2_extattr_delete_value(off, first_entry, entry, end);

	/* Clean the entry */
	next = first_entry;
	while (!EXT2_IS_LAST_ENTRY(next))
		next = EXT2_EXTATTR_NEXT(next);

	pad = (char*)next + sizeof(uint32_t);

	memmove(entry, (char *)entry + EXT2_EXTATTR_LEN(entry->e_name_len),
	    pad - ((char *)entry + EXT2_EXTATTR_LEN(entry->e_name_len)));
}