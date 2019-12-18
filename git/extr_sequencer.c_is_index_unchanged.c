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
struct repository {struct index_state* index; } ;
struct object_id {int dummy; } ;
struct index_state {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 struct object_id* get_cache_tree_oid (struct index_state*) ; 
 int /*<<< orphan*/  get_commit_tree_oid (struct commit*) ; 
 struct commit* lookup_commit (struct repository*,struct object_id*) ; 
 int oideq (struct object_id*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  resolve_ref_unsafe (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_index_unchanged(struct repository *r)
{
	struct object_id head_oid, *cache_tree_oid;
	struct commit *head_commit;
	struct index_state *istate = r->index;

	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, &head_oid, NULL))
		return error(_("could not resolve HEAD commit"));

	head_commit = lookup_commit(r, &head_oid);

	/*
	 * If head_commit is NULL, check_commit, called from
	 * lookup_commit, would have indicated that head_commit is not
	 * a commit object already.  parse_commit() will return failure
	 * without further complaints in such a case.  Otherwise, if
	 * the commit is invalid, parse_commit() will complain.  So
	 * there is nothing for us to say here.  Just return failure.
	 */
	if (parse_commit(head_commit))
		return -1;

	if (!(cache_tree_oid = get_cache_tree_oid(istate)))
		return -1;

	return oideq(cache_tree_oid, get_commit_tree_oid(head_commit));
}