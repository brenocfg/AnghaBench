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
struct object {scalar_t__ type; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 struct object* deref_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int is_descendant_of (struct commit*,struct commit_list*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

int ref_newer(const struct object_id *new_oid, const struct object_id *old_oid)
{
	struct object *o;
	struct commit *old_commit, *new_commit;
	struct commit_list *old_commit_list = NULL;

	/*
	 * Both new_commit and old_commit must be commit-ish and new_commit is descendant of
	 * old_commit.  Otherwise we require --force.
	 */
	o = deref_tag(the_repository, parse_object(the_repository, old_oid),
		      NULL, 0);
	if (!o || o->type != OBJ_COMMIT)
		return 0;
	old_commit = (struct commit *) o;

	o = deref_tag(the_repository, parse_object(the_repository, new_oid),
		      NULL, 0);
	if (!o || o->type != OBJ_COMMIT)
		return 0;
	new_commit = (struct commit *) o;

	if (parse_commit(new_commit) < 0)
		return 0;

	commit_list_insert(old_commit, &old_commit_list);
	return is_descendant_of(new_commit, old_commit_list);
}