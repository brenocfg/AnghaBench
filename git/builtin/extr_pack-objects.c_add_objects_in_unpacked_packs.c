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
struct packed_git {size_t num_objects; scalar_t__ pack_keep_in_core; scalar_t__ pack_keep; int /*<<< orphan*/  pack_local; struct packed_git* next; } ;
struct object_id {int dummy; } ;
struct object {int flags; int /*<<< orphan*/  type; int /*<<< orphan*/  oid; } ;
struct in_pack {size_t nr; TYPE_1__* array; int /*<<< orphan*/  alloc; } ;
typedef  int /*<<< orphan*/  in_pack ;
struct TYPE_4__ {struct object* object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int OBJECT_ADDED ; 
 int /*<<< orphan*/  QSORT (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_object_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 struct packed_git* get_all_packs (int /*<<< orphan*/ ) ; 
 struct object* lookup_unknown_object (struct object_id*) ; 
 int /*<<< orphan*/  mark_in_pack_object (struct object*,struct packed_git*,struct in_pack*) ; 
 int /*<<< orphan*/  memset (struct in_pack*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nth_packed_object_oid (struct object_id*,struct packed_git*,size_t) ; 
 int /*<<< orphan*/  ofscmp ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void add_objects_in_unpacked_packs(void)
{
	struct packed_git *p;
	struct in_pack in_pack;
	uint32_t i;

	memset(&in_pack, 0, sizeof(in_pack));

	for (p = get_all_packs(the_repository); p; p = p->next) {
		struct object_id oid;
		struct object *o;

		if (!p->pack_local || p->pack_keep || p->pack_keep_in_core)
			continue;
		if (open_pack_index(p))
			die(_("cannot open pack index"));

		ALLOC_GROW(in_pack.array,
			   in_pack.nr + p->num_objects,
			   in_pack.alloc);

		for (i = 0; i < p->num_objects; i++) {
			nth_packed_object_oid(&oid, p, i);
			o = lookup_unknown_object(&oid);
			if (!(o->flags & OBJECT_ADDED))
				mark_in_pack_object(o, p, &in_pack);
			o->flags |= OBJECT_ADDED;
		}
	}

	if (in_pack.nr) {
		QSORT(in_pack.array, in_pack.nr, ofscmp);
		for (i = 0; i < in_pack.nr; i++) {
			struct object *o = in_pack.array[i].object;
			add_object_entry(&o->oid, o->type, "", 0);
		}
	}
	free(in_pack.array);
}