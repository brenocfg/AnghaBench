#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shallow_info {int nr_ours; int nr_theirs; size_t* ours; size_t* theirs; TYPE_1__* shallow; struct oid_array* ref; } ;
struct object_id {int dummy; } ;
struct ref {int /*<<< orphan*/  status; struct object_id old_oid; } ;
struct oid_array {scalar_t__ nr; } ;
struct fetch_pack_args {scalar_t__ update_shallow; scalar_t__ cloning; scalar_t__ deepen; } ;
struct TYPE_2__ {int nr; struct object_id* oid; } ;

/* Variables and functions */
 struct oid_array OID_ARRAY_INIT ; 
 int /*<<< orphan*/  REF_STATUS_REJECT_SHALLOW ; 
 char* alternate_shallow_file ; 
 int /*<<< orphan*/  assign_shallow_commits_to_refs (struct shallow_info*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  commit_lock_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  git_path_shallow (int /*<<< orphan*/ ) ; 
 scalar_t__ has_object_file (struct object_id*) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id*) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int /*<<< orphan*/  remove_nonexistent_theirs_shallow (struct shallow_info*) ; 
 int /*<<< orphan*/  rollback_lock_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_alternate_shallow (int /*<<< orphan*/ *,char**,struct oid_array*) ; 
 int /*<<< orphan*/  shallow_lock ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 
 int* xcalloc (int,int) ; 

__attribute__((used)) static void update_shallow(struct fetch_pack_args *args,
			   struct ref **sought, int nr_sought,
			   struct shallow_info *si)
{
	struct oid_array ref = OID_ARRAY_INIT;
	int *status;
	int i;

	if (args->deepen && alternate_shallow_file) {
		if (*alternate_shallow_file == '\0') { /* --unshallow */
			unlink_or_warn(git_path_shallow(the_repository));
			rollback_lock_file(&shallow_lock);
		} else
			commit_lock_file(&shallow_lock);
		alternate_shallow_file = NULL;
		return;
	}

	if (!si->shallow || !si->shallow->nr)
		return;

	if (args->cloning) {
		/*
		 * remote is shallow, but this is a clone, there are
		 * no objects in repo to worry about. Accept any
		 * shallow points that exist in the pack (iow in repo
		 * after get_pack() and reprepare_packed_git())
		 */
		struct oid_array extra = OID_ARRAY_INIT;
		struct object_id *oid = si->shallow->oid;
		for (i = 0; i < si->shallow->nr; i++)
			if (has_object_file(&oid[i]))
				oid_array_append(&extra, &oid[i]);
		if (extra.nr) {
			setup_alternate_shallow(&shallow_lock,
						&alternate_shallow_file,
						&extra);
			commit_lock_file(&shallow_lock);
			alternate_shallow_file = NULL;
		}
		oid_array_clear(&extra);
		return;
	}

	if (!si->nr_ours && !si->nr_theirs)
		return;

	remove_nonexistent_theirs_shallow(si);
	if (!si->nr_ours && !si->nr_theirs)
		return;
	for (i = 0; i < nr_sought; i++)
		oid_array_append(&ref, &sought[i]->old_oid);
	si->ref = &ref;

	if (args->update_shallow) {
		/*
		 * remote is also shallow, .git/shallow may be updated
		 * so all refs can be accepted. Make sure we only add
		 * shallow roots that are actually reachable from new
		 * refs.
		 */
		struct oid_array extra = OID_ARRAY_INIT;
		struct object_id *oid = si->shallow->oid;
		assign_shallow_commits_to_refs(si, NULL, NULL);
		if (!si->nr_ours && !si->nr_theirs) {
			oid_array_clear(&ref);
			return;
		}
		for (i = 0; i < si->nr_ours; i++)
			oid_array_append(&extra, &oid[si->ours[i]]);
		for (i = 0; i < si->nr_theirs; i++)
			oid_array_append(&extra, &oid[si->theirs[i]]);
		setup_alternate_shallow(&shallow_lock,
					&alternate_shallow_file,
					&extra);
		commit_lock_file(&shallow_lock);
		oid_array_clear(&extra);
		oid_array_clear(&ref);
		alternate_shallow_file = NULL;
		return;
	}

	/*
	 * remote is also shallow, check what ref is safe to update
	 * without updating .git/shallow
	 */
	status = xcalloc(nr_sought, sizeof(*status));
	assign_shallow_commits_to_refs(si, NULL, status);
	if (si->nr_ours || si->nr_theirs) {
		for (i = 0; i < nr_sought; i++)
			if (status[i])
				sought[i]->status = REF_STATUS_REJECT_SHALLOW;
	}
	free(status);
	oid_array_clear(&ref);
}