#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct index_entry_offset_table {int nr; TYPE_1__* entries; } ;
struct index_entry_offset {int dummy; } ;
struct TYPE_4__ {size_t rawsz; } ;
struct TYPE_3__ {void* nr; void* offset; } ;

/* Variables and functions */
 scalar_t__ CACHE_EXT (char const*) ; 
 scalar_t__ CACHE_EXT_INDEXENTRYOFFSETTABLE ; 
 size_t IEOT_VERSION ; 
 int /*<<< orphan*/  error (char*,int) ; 
 void* get_be32 (char const*) ; 
 TYPE_2__* the_hash_algo ; 
 struct index_entry_offset_table* xmalloc (int) ; 

__attribute__((used)) static struct index_entry_offset_table *read_ieot_extension(const char *mmap, size_t mmap_size, size_t offset)
{
	const char *index = NULL;
	uint32_t extsize, ext_version;
	struct index_entry_offset_table *ieot;
	int i, nr;

	/* find the IEOT extension */
	if (!offset)
		return NULL;
	while (offset <= mmap_size - the_hash_algo->rawsz - 8) {
		extsize = get_be32(mmap + offset + 4);
		if (CACHE_EXT((mmap + offset)) == CACHE_EXT_INDEXENTRYOFFSETTABLE) {
			index = mmap + offset + 4 + 4;
			break;
		}
		offset += 8;
		offset += extsize;
	}
	if (!index)
		return NULL;

	/* validate the version is IEOT_VERSION */
	ext_version = get_be32(index);
	if (ext_version != IEOT_VERSION) {
		error("invalid IEOT version %d", ext_version);
		return NULL;
	}
	index += sizeof(uint32_t);

	/* extension size - version bytes / bytes per entry */
	nr = (extsize - sizeof(uint32_t)) / (sizeof(uint32_t) + sizeof(uint32_t));
	if (!nr) {
		error("invalid number of IEOT entries %d", nr);
		return NULL;
	}
	ieot = xmalloc(sizeof(struct index_entry_offset_table)
		       + (nr * sizeof(struct index_entry_offset)));
	ieot->nr = nr;
	for (i = 0; i < nr; i++) {
		ieot->entries[i].offset = get_be32(index);
		index += sizeof(uint32_t);
		ieot->entries[i].nr = get_be32(index);
		index += sizeof(uint32_t);
	}

	return ieot;
}