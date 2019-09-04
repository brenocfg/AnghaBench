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
struct object_id {int dummy; } ;
struct notes_tree {int dummy; } ;
typedef  int /*<<< orphan*/  combine_notes_fn ;

/* Variables and functions */
 int add_note (struct notes_tree*,struct object_id const*,struct object_id const*,int /*<<< orphan*/ ) ; 
 struct object_id* get_note (struct notes_tree*,struct object_id const*) ; 
 struct object_id const null_oid ; 

int copy_note(struct notes_tree *t,
	      const struct object_id *from_obj, const struct object_id *to_obj,
	      int force, combine_notes_fn combine_notes)
{
	const struct object_id *note = get_note(t, from_obj);
	const struct object_id *existing_note = get_note(t, to_obj);

	if (!force && existing_note)
		return 1;

	if (note)
		return add_note(t, to_obj, note, combine_notes);
	else if (existing_note)
		return add_note(t, to_obj, &null_oid, combine_notes);

	return 0;
}