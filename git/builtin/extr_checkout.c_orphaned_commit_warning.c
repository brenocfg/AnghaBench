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
struct rev_info {int dummy; } ;
struct object {int flags; int /*<<< orphan*/  oid; } ;
struct commit {struct object object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_REV_FLAGS ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_pending_oid (struct rev_info*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_pending_uninteresting_ref ; 
 int /*<<< orphan*/  clear_commit_marks_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  describe_detached_head (int /*<<< orphan*/ ,struct commit*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct rev_info*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suggest_reattach (struct commit*,struct rev_info*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void orphaned_commit_warning(struct commit *old_commit, struct commit *new_commit)
{
	struct rev_info revs;
	struct object *object = &old_commit->object;

	repo_init_revisions(the_repository, &revs, NULL);
	setup_revisions(0, NULL, &revs, NULL);

	object->flags &= ~UNINTERESTING;
	add_pending_object(&revs, object, oid_to_hex(&object->oid));

	for_each_ref(add_pending_uninteresting_ref, &revs);
	if (new_commit)
		add_pending_oid(&revs, "HEAD",
				&new_commit->object.oid,
				UNINTERESTING);

	if (prepare_revision_walk(&revs))
		die(_("internal error in revision walk"));
	if (!(old_commit->object.flags & UNINTERESTING))
		suggest_reattach(old_commit, &revs);
	else
		describe_detached_head(_("Previous HEAD position was"), old_commit);

	/* Clean up objects used, as they will be reused. */
	clear_commit_marks_all(ALL_REV_FLAGS);
}