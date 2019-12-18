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
typedef  scalar_t__ timestamp_t ;
struct ref {int /*<<< orphan*/  old_oid; struct ref* next; } ;
struct object {scalar_t__ type; int flags; } ;
struct fetch_pack_args {int /*<<< orphan*/  deepen; } ;
struct fetch_negotiator {int /*<<< orphan*/  (* known_common ) (struct fetch_negotiator*,struct commit*) ;} ;
struct commit {scalar_t__ date; } ;

/* Variables and functions */
 int COMPLETE ; 
 int /*<<< orphan*/  OBJECT_INFO_QUICK ; 
 scalar_t__ OBJ_COMMIT ; 
 int /*<<< orphan*/  commit_list_sort_by_date (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete ; 
 struct object* deref_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_cached_alternate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_object_file_with_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_alternate_complete ; 
 int /*<<< orphan*/  mark_complete_oid ; 
 int /*<<< orphan*/  mark_recent_complete_commits (struct fetch_pack_args*,scalar_t__) ; 
 struct object* parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int save_commit_buffer ; 
 int /*<<< orphan*/  stub1 (struct fetch_negotiator*,struct commit*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void mark_complete_and_common_ref(struct fetch_negotiator *negotiator,
					 struct fetch_pack_args *args,
					 struct ref **refs)
{
	struct ref *ref;
	int old_save_commit_buffer = save_commit_buffer;
	timestamp_t cutoff = 0;

	save_commit_buffer = 0;

	for (ref = *refs; ref; ref = ref->next) {
		struct object *o;

		if (!has_object_file_with_flags(&ref->old_oid,
						OBJECT_INFO_QUICK))
			continue;
		o = parse_object(the_repository, &ref->old_oid);
		if (!o)
			continue;

		/* We already have it -- which may mean that we were
		 * in sync with the other side at some time after
		 * that (it is OK if we guess wrong here).
		 */
		if (o->type == OBJ_COMMIT) {
			struct commit *commit = (struct commit *)o;
			if (!cutoff || cutoff < commit->date)
				cutoff = commit->date;
		}
	}

	if (!args->deepen) {
		for_each_ref(mark_complete_oid, NULL);
		for_each_cached_alternate(NULL, mark_alternate_complete);
		commit_list_sort_by_date(&complete);
		if (cutoff)
			mark_recent_complete_commits(args, cutoff);
	}

	/*
	 * Mark all complete remote refs as common refs.
	 * Don't mark them common yet; the server has to be told so first.
	 */
	for (ref = *refs; ref; ref = ref->next) {
		struct object *o = deref_tag(the_repository,
					     lookup_object(the_repository,
					     &ref->old_oid),
					     NULL, 0);

		if (!o || o->type != OBJ_COMMIT || !(o->flags & COMPLETE))
			continue;

		negotiator->known_common(negotiator,
					 (struct commit *)o);
	}

	save_commit_buffer = old_save_commit_buffer;
}