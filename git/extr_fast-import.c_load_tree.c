#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tree_entry {TYPE_1__* versions; TYPE_2__* name; struct tree_content* tree; } ;
struct tree_content {scalar_t__ entry_count; scalar_t__ entry_capacity; struct tree_entry** entries; int /*<<< orphan*/  delta_depth; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct object_entry {scalar_t__ pack_id; scalar_t__ type; int /*<<< orphan*/  depth; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_6__ {int /*<<< orphan*/  rawsz; } ;
struct TYPE_5__ {scalar_t__ str_len; } ;
struct TYPE_4__ {struct object_id oid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ MAX_PACK_ID ; 
 scalar_t__ OBJ_TREE ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 struct object_entry* find_object (struct object_id*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_mode (char const*,int /*<<< orphan*/ *) ; 
 char* gfi_unpack_entry (struct object_entry*,unsigned long*) ; 
 struct tree_content* grow_tree_content (struct tree_content*,scalar_t__) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 struct tree_content* new_tree_content (int) ; 
 struct tree_entry* new_tree_entry () ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 char* read_object_file (struct object_id*,int*,unsigned long*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_3__* the_hash_algo ; 
 TYPE_2__* to_atom (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_tree(struct tree_entry *root)
{
	struct object_id *oid = &root->versions[1].oid;
	struct object_entry *myoe;
	struct tree_content *t;
	unsigned long size;
	char *buf;
	const char *c;

	root->tree = t = new_tree_content(8);
	if (is_null_oid(oid))
		return;

	myoe = find_object(oid);
	if (myoe && myoe->pack_id != MAX_PACK_ID) {
		if (myoe->type != OBJ_TREE)
			die("Not a tree: %s", oid_to_hex(oid));
		t->delta_depth = myoe->depth;
		buf = gfi_unpack_entry(myoe, &size);
		if (!buf)
			die("Can't load tree %s", oid_to_hex(oid));
	} else {
		enum object_type type;
		buf = read_object_file(oid, &type, &size);
		if (!buf || type != OBJ_TREE)
			die("Can't load tree %s", oid_to_hex(oid));
	}

	c = buf;
	while (c != (buf + size)) {
		struct tree_entry *e = new_tree_entry();

		if (t->entry_count == t->entry_capacity)
			root->tree = t = grow_tree_content(t, t->entry_count);
		t->entries[t->entry_count++] = e;

		e->tree = NULL;
		c = get_mode(c, &e->versions[1].mode);
		if (!c)
			die("Corrupt mode in %s", oid_to_hex(oid));
		e->versions[0].mode = e->versions[1].mode;
		e->name = to_atom(c, strlen(c));
		c += e->name->str_len + 1;
		hashcpy(e->versions[0].oid.hash, (unsigned char *)c);
		hashcpy(e->versions[1].oid.hash, (unsigned char *)c);
		c += the_hash_algo->rawsz;
	}
	free(buf);
}