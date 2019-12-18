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
struct ext2fs_extattr_entry {int e_name_len; int e_value_size; } ;

/* Variables and functions */
 scalar_t__ EXT2_EXTATTR_LEN (int) ; 
 struct ext2fs_extattr_entry* EXT2_EXTATTR_NEXT (struct ext2fs_extattr_entry*) ; 
 scalar_t__ EXT2_EXTATTR_SIZE (int) ; 
 int /*<<< orphan*/  EXT2_IS_LAST_ENTRY (struct ext2fs_extattr_entry*) ; 

__attribute__((used)) static int
ext2_extattr_get_size(struct ext2fs_extattr_entry *first_entry,
    struct ext2fs_extattr_entry *exist_entry, int header_size,
    int name_len, int new_size)
{
	struct ext2fs_extattr_entry *entry;
	int size;

	size = header_size;
	size += sizeof(uint32_t);

	if (NULL == exist_entry) {
		size += EXT2_EXTATTR_LEN(name_len);
		size += EXT2_EXTATTR_SIZE(new_size);
	}

	if (first_entry)
		for (entry = first_entry; !EXT2_IS_LAST_ENTRY(entry);
		    entry = EXT2_EXTATTR_NEXT(entry)) {
			if (entry != exist_entry)
				size += EXT2_EXTATTR_LEN(entry->e_name_len) +
				    EXT2_EXTATTR_SIZE(entry->e_value_size);
			else
				size += EXT2_EXTATTR_LEN(entry->e_name_len) +
				    EXT2_EXTATTR_SIZE(new_size);
		}

	return (size);
}