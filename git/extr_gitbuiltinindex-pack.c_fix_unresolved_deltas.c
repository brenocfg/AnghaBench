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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hash; } ;
struct ref_delta_entry {size_t obj_no; TYPE_1__ oid; } ;
struct hashfile {int dummy; } ;
struct base_data {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  obj; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_6__ {scalar_t__ real_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct ref_delta_entry**,int) ; 
 scalar_t__ OBJ_REF_DELTA ; 
 int /*<<< orphan*/  QSORT (struct ref_delta_entry**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct base_data* alloc_base_data () ; 
 int /*<<< orphan*/  append_obj_to_pack (struct hashfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_object_signature (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delta_pos_compare ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_unresolved_deltas (struct base_data*) ; 
 int /*<<< orphan*/  free (struct ref_delta_entry**) ; 
 int nr_ref_deltas ; 
 int /*<<< orphan*/  nr_resolved_deltas ; 
 TYPE_3__* objects ; 
 int /*<<< orphan*/  oid_to_hex (TYPE_1__*) ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  read_object_file (TYPE_1__*,int*,int /*<<< orphan*/ *) ; 
 struct ref_delta_entry* ref_deltas ; 
 int /*<<< orphan*/  type_name (int) ; 

__attribute__((used)) static void fix_unresolved_deltas(struct hashfile *f)
{
	struct ref_delta_entry **sorted_by_pos;
	int i;

	/*
	 * Since many unresolved deltas may well be themselves base objects
	 * for more unresolved deltas, we really want to include the
	 * smallest number of base objects that would cover as much delta
	 * as possible by picking the
	 * trunc deltas first, allowing for other deltas to resolve without
	 * additional base objects.  Since most base objects are to be found
	 * before deltas depending on them, a good heuristic is to start
	 * resolving deltas in the same order as their position in the pack.
	 */
	ALLOC_ARRAY(sorted_by_pos, nr_ref_deltas);
	for (i = 0; i < nr_ref_deltas; i++)
		sorted_by_pos[i] = &ref_deltas[i];
	QSORT(sorted_by_pos, nr_ref_deltas, delta_pos_compare);

	for (i = 0; i < nr_ref_deltas; i++) {
		struct ref_delta_entry *d = sorted_by_pos[i];
		enum object_type type;
		struct base_data *base_obj = alloc_base_data();

		if (objects[d->obj_no].real_type != OBJ_REF_DELTA)
			continue;
		base_obj->data = read_object_file(&d->oid, &type,
						  &base_obj->size);
		if (!base_obj->data)
			continue;

		if (check_object_signature(&d->oid, base_obj->data,
				base_obj->size, type_name(type)))
			die(_("local object %s is corrupt"), oid_to_hex(&d->oid));
		base_obj->obj = append_obj_to_pack(f, d->oid.hash,
					base_obj->data, base_obj->size, type);
		find_unresolved_deltas(base_obj);
		display_progress(progress, nr_resolved_deltas);
	}
	free(sorted_by_pos);
}