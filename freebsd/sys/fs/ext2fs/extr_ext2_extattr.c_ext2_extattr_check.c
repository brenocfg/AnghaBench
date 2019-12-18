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
struct ext2fs_extattr_entry {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct ext2fs_extattr_entry* EXT2_EXTATTR_NEXT (struct ext2fs_extattr_entry*) ; 
 int /*<<< orphan*/  EXT2_IS_LAST_ENTRY (struct ext2fs_extattr_entry*) ; 

__attribute__((used)) static int
ext2_extattr_check(struct ext2fs_extattr_entry *entry, char *end)
{
	struct ext2fs_extattr_entry *next;

	while (!EXT2_IS_LAST_ENTRY(entry)) {
		next = EXT2_EXTATTR_NEXT(entry);
		if ((char *)next >= end)
			return (EIO);

		entry = next;
	}

	return (0);
}