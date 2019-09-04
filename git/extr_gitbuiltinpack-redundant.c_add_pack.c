#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct packed_git {unsigned char* index_data; int index_version; unsigned long num_objects; scalar_t__ pack_local; } ;
struct pack_list {int /*<<< orphan*/ * unique_objects; TYPE_2__* remaining_objects; int /*<<< orphan*/  all_objects_size; struct packed_git* pack; } ;
struct object_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int rawsz; } ;

/* Variables and functions */
 scalar_t__ alt_odb ; 
 int /*<<< orphan*/  altodb_packs ; 
 int /*<<< orphan*/  llist_init (TYPE_2__**) ; 
 int /*<<< orphan*/  llist_insert_back (TYPE_2__*,struct object_id const*) ; 
 int /*<<< orphan*/  local_packs ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 
 struct pack_list* pack_list_insert (int /*<<< orphan*/ *,struct pack_list*) ; 
 TYPE_1__* the_hash_algo ; 
 scalar_t__ verbose ; 

__attribute__((used)) static struct pack_list * add_pack(struct packed_git *p)
{
	struct pack_list l;
	unsigned long off = 0, step;
	const unsigned char *base;

	if (!p->pack_local && !(alt_odb || verbose))
		return NULL;

	l.pack = p;
	llist_init(&l.remaining_objects);

	if (open_pack_index(p))
		return NULL;

	base = p->index_data;
	base += 256 * 4 + ((p->index_version < 2) ? 4 : 8);
	step = the_hash_algo->rawsz + ((p->index_version < 2) ? 4 : 0);
	while (off < p->num_objects * step) {
		llist_insert_back(l.remaining_objects, (const struct object_id *)(base + off));
		off += step;
	}
	l.all_objects_size = l.remaining_objects->size;
	l.unique_objects = NULL;
	if (p->pack_local)
		return pack_list_insert(&local_packs, &l);
	else
		return pack_list_insert(&altodb_packs, &l);
}