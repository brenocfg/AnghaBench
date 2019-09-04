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
struct packing_data {int /*<<< orphan*/  repo; int /*<<< orphan*/  nr_objects; int /*<<< orphan*/  in_pack_pos; } ;
struct pack_idx_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct object_entry {TYPE_1__ idx; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {void* tags; void* blobs; void* trees; void* commits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  OBJ_BLOB 131 
#define  OBJ_COMMIT 130 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int,int) ; 
 void* ewah_new () ; 
 int /*<<< orphan*/  ewah_set (void*,size_t) ; 
 int /*<<< orphan*/  oe_set_in_pack_pos (struct packing_data*,struct object_entry*,size_t) ; 
 int oe_type (struct object_entry*) ; 
 int oid_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 TYPE_2__ writer ; 

void bitmap_writer_build_type_index(struct packing_data *to_pack,
				    struct pack_idx_entry **index,
				    uint32_t index_nr)
{
	uint32_t i;

	writer.commits = ewah_new();
	writer.trees = ewah_new();
	writer.blobs = ewah_new();
	writer.tags = ewah_new();
	ALLOC_ARRAY(to_pack->in_pack_pos, to_pack->nr_objects);

	for (i = 0; i < index_nr; ++i) {
		struct object_entry *entry = (struct object_entry *)index[i];
		enum object_type real_type;

		oe_set_in_pack_pos(to_pack, entry, i);

		switch (oe_type(entry)) {
		case OBJ_COMMIT:
		case OBJ_TREE:
		case OBJ_BLOB:
		case OBJ_TAG:
			real_type = oe_type(entry);
			break;

		default:
			real_type = oid_object_info(to_pack->repo,
						    &entry->idx.oid, NULL);
			break;
		}

		switch (real_type) {
		case OBJ_COMMIT:
			ewah_set(writer.commits, i);
			break;

		case OBJ_TREE:
			ewah_set(writer.trees, i);
			break;

		case OBJ_BLOB:
			ewah_set(writer.blobs, i);
			break;

		case OBJ_TAG:
			ewah_set(writer.tags, i);
			break;

		default:
			die("Missing type information for %s (%d/%d)",
			    oid_to_hex(&entry->idx.oid), real_type,
			    oe_type(entry));
		}
	}
}