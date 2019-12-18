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
struct commit {int dummy; } ;
struct branch {int dummy; } ;

/* Variables and functions */
 int FILTER_REFS_BRANCHES ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct branch* branch_get (char const*) ; 
 char* branch_get_upstream (struct branch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int in_merge_bases (struct commit*,struct commit*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 void* resolve_refdup (char const*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static int branch_merged(int kind, const char *name,
			 struct commit *rev, struct commit *head_rev)
{
	/*
	 * This checks whether the merge bases of branch and HEAD (or
	 * the other branch this branch builds upon) contains the
	 * branch, which means that the branch has already been merged
	 * safely to HEAD (or the other branch).
	 */
	struct commit *reference_rev = NULL;
	const char *reference_name = NULL;
	void *reference_name_to_free = NULL;
	int merged;

	if (kind == FILTER_REFS_BRANCHES) {
		struct branch *branch = branch_get(name);
		const char *upstream = branch_get_upstream(branch, NULL);
		struct object_id oid;

		if (upstream &&
		    (reference_name = reference_name_to_free =
		     resolve_refdup(upstream, RESOLVE_REF_READING,
				    &oid, NULL)) != NULL)
			reference_rev = lookup_commit_reference(the_repository,
								&oid);
	}
	if (!reference_rev)
		reference_rev = head_rev;

	merged = in_merge_bases(rev, reference_rev);

	/*
	 * After the safety valve is fully redefined to "check with
	 * upstream, if any, otherwise with HEAD", we should just
	 * return the result of the in_merge_bases() above without
	 * any of the following code, but during the transition period,
	 * a gentle reminder is in order.
	 */
	if ((head_rev != reference_rev) &&
	    in_merge_bases(rev, head_rev) != merged) {
		if (merged)
			warning(_("deleting branch '%s' that has been merged to\n"
				"         '%s', but not yet merged to HEAD."),
				name, reference_name);
		else
			warning(_("not deleting branch '%s' that is not yet merged to\n"
				"         '%s', even though it is merged to HEAD."),
				name, reference_name);
	}
	free(reference_name_to_free);
	return merged;
}