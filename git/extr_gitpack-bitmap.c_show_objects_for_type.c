#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct revindex_entry {int /*<<< orphan*/  offset; scalar_t__ nr; } ;
struct object_id {int dummy; } ;
struct ewah_iterator {int dummy; } ;
struct ewah_bitmap {int dummy; } ;
struct bitmap_index {scalar_t__ reuse_objects; TYPE_1__* pack; scalar_t__ hashes; struct bitmap* result; } ;
struct bitmap {size_t word_alloc; size_t* words; } ;
typedef  int /*<<< orphan*/  (* show_reachable_fn ) (struct object_id*,int,int /*<<< orphan*/ ,size_t,TYPE_1__*,int /*<<< orphan*/ ) ;
typedef  size_t eword_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {scalar_t__ num_objects; struct revindex_entry* revindex; } ;

/* Variables and functions */
 size_t BITS_IN_EWORD ; 
 scalar_t__ ewah_bit_ctz64 (size_t) ; 
 int /*<<< orphan*/  ewah_iterator_init (struct ewah_iterator*,struct ewah_bitmap*) ; 
 scalar_t__ ewah_iterator_next (size_t*,struct ewah_iterator*) ; 
 size_t get_be32 (scalar_t__) ; 
 int /*<<< orphan*/  nth_packed_object_oid (struct object_id*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void show_objects_for_type(
	struct bitmap_index *bitmap_git,
	struct ewah_bitmap *type_filter,
	enum object_type object_type,
	show_reachable_fn show_reach)
{
	size_t pos = 0, i = 0;
	uint32_t offset;

	struct ewah_iterator it;
	eword_t filter;

	struct bitmap *objects = bitmap_git->result;

	if (bitmap_git->reuse_objects == bitmap_git->pack->num_objects)
		return;

	ewah_iterator_init(&it, type_filter);

	while (i < objects->word_alloc && ewah_iterator_next(&filter, &it)) {
		eword_t word = objects->words[i] & filter;

		for (offset = 0; offset < BITS_IN_EWORD; ++offset) {
			struct object_id oid;
			struct revindex_entry *entry;
			uint32_t hash = 0;

			if ((word >> offset) == 0)
				break;

			offset += ewah_bit_ctz64(word >> offset);

			if (pos + offset < bitmap_git->reuse_objects)
				continue;

			entry = &bitmap_git->pack->revindex[pos + offset];
			nth_packed_object_oid(&oid, bitmap_git->pack, entry->nr);

			if (bitmap_git->hashes)
				hash = get_be32(bitmap_git->hashes + entry->nr);

			show_reach(&oid, object_type, 0, hash, bitmap_git->pack, entry->offset);
		}

		pos += BITS_IN_EWORD;
		i++;
	}
}