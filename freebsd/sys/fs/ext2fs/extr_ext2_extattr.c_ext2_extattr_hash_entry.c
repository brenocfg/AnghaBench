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
struct ext2fs_extattr_header {int dummy; } ;
struct ext2fs_extattr_entry {char* e_name; int e_name_len; scalar_t__ e_value_block; int e_value_size; int e_value_offs; int e_hash; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int EXT2_EXTATTR_NAME_HASH_SHIFT ; 
 int EXT2_EXTATTR_PAD_BITS ; 
 int EXT2_EXTATTR_ROUND ; 
 int EXT2_EXTATTR_VALUE_HASH_SHIFT ; 

__attribute__((used)) static void
ext2_extattr_hash_entry(struct ext2fs_extattr_header *header,
    struct ext2fs_extattr_entry *entry)
{
	uint32_t hash = 0;
	char *name = entry->e_name;
	int n;

	for (n=0; n < entry->e_name_len; n++) {
		hash = (hash << EXT2_EXTATTR_NAME_HASH_SHIFT) ^
		    (hash >> (8*sizeof(hash) - EXT2_EXTATTR_NAME_HASH_SHIFT)) ^
		    (*name++);
	}

	if (entry->e_value_block == 0 && entry->e_value_size != 0) {
		uint32_t *value = (uint32_t *)((char *)header + entry->e_value_offs);
		for (n = (entry->e_value_size +
		    EXT2_EXTATTR_ROUND) >> EXT2_EXTATTR_PAD_BITS; n; n--) {
			hash = (hash << EXT2_EXTATTR_VALUE_HASH_SHIFT) ^
			    (hash >> (8*sizeof(hash) - EXT2_EXTATTR_VALUE_HASH_SHIFT)) ^
			    (*value++);
		}
	}

	entry->e_hash = hash;
}