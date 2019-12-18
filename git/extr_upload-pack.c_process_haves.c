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
struct oid_array {int nr; struct object_id* oid; } ;
struct object_id {int dummy; } ;
struct object_array {int dummy; } ;
struct object {scalar_t__ type; int flags; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {scalar_t__ date; struct commit_list* parents; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 int THEY_HAVE ; 
 int /*<<< orphan*/  add_object_array (struct object*,int /*<<< orphan*/ *,struct object_array*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_object_file (struct object_id const*) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id const*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 scalar_t__ oldest_have ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int process_haves(struct oid_array *haves, struct oid_array *common,
			 struct object_array *have_obj)
{
	int i;

	/* Process haves */
	for (i = 0; i < haves->nr; i++) {
		const struct object_id *oid = &haves->oid[i];
		struct object *o;
		int we_knew_they_have = 0;

		if (!has_object_file(oid))
			continue;

		oid_array_append(common, oid);

		o = parse_object(the_repository, oid);
		if (!o)
			die("oops (%s)", oid_to_hex(oid));
		if (o->type == OBJ_COMMIT) {
			struct commit_list *parents;
			struct commit *commit = (struct commit *)o;
			if (o->flags & THEY_HAVE)
				we_knew_they_have = 1;
			else
				o->flags |= THEY_HAVE;
			if (!oldest_have || (commit->date < oldest_have))
				oldest_have = commit->date;
			for (parents = commit->parents;
			     parents;
			     parents = parents->next)
				parents->item->object.flags |= THEY_HAVE;
		}
		if (!we_knew_they_have)
			add_object_array(o, NULL, have_obj);
	}

	return 0;
}