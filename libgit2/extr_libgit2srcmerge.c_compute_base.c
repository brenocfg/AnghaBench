#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_15__ {size_t count; int /*<<< orphan*/ * ids; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_oidarray ;
struct TYPE_16__ {int flags; size_t recursion_limit; } ;
typedef  TYPE_2__ git_merge_options ;
struct TYPE_17__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ git_array_oid_t ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 TYPE_3__ GIT_ARRAY_INIT ; 
 int GIT_MERGE_NO_RECURSIVE ; 
 TYPE_2__ GIT_MERGE_OPTIONS_INIT ; 
 int create_virtual_base (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_array_clear (TYPE_3__) ; 
 int git_merge_bases_many (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oidarray__reverse (TYPE_1__*) ; 
 int /*<<< orphan*/  git_oidarray_free (TYPE_1__*) ; 
 int insert_head_ids (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static int compute_base(
	git_annotated_commit **out,
	git_repository *repo,
	const git_annotated_commit *one,
	const git_annotated_commit *two,
	const git_merge_options *given_opts,
	size_t recursion_level)
{
	git_array_oid_t head_ids = GIT_ARRAY_INIT;
	git_oidarray bases = {0};
	git_annotated_commit *base = NULL, *other = NULL, *new_base = NULL;
	git_merge_options opts = GIT_MERGE_OPTIONS_INIT;
	size_t i, base_count;
	int error;

	*out = NULL;

	if (given_opts)
		memcpy(&opts, given_opts, sizeof(git_merge_options));

	/* With more than two commits, merge_bases_many finds the base of
	 * the first commit and a hypothetical merge of the others. Since
	 * "one" may itself be a virtual commit, which insert_head_ids
	 * substitutes multiple ancestors for, it needs to be added
	 * after "two" which is always a single real commit.
	 */
	if ((error = insert_head_ids(&head_ids, two)) < 0 ||
		(error = insert_head_ids(&head_ids, one)) < 0 ||
		(error = git_merge_bases_many(&bases, repo,
			head_ids.size, head_ids.ptr)) < 0)
		goto done;

	base_count = (opts.flags & GIT_MERGE_NO_RECURSIVE) ? 0 : bases.count;

	if (base_count)
		git_oidarray__reverse(&bases);

	if ((error = git_annotated_commit_lookup(&base, repo, &bases.ids[0])) < 0)
		goto done;

	for (i = 1; i < base_count; i++) {
		recursion_level++;

		if (opts.recursion_limit && recursion_level > opts.recursion_limit)
			break;

		if ((error = git_annotated_commit_lookup(&other, repo,
				&bases.ids[i])) < 0 ||
			(error = create_virtual_base(&new_base, repo, base, other, &opts,
				recursion_level)) < 0)
			goto done;

		git_annotated_commit_free(base);
		git_annotated_commit_free(other);

		base = new_base;
		new_base = NULL;
		other = NULL;
	}

done:
	if (error == 0)
		*out = base;
	else
		git_annotated_commit_free(base);

	git_annotated_commit_free(other);
	git_annotated_commit_free(new_base);
	git_oidarray_free(&bases);
	git_array_clear(head_ids);
	return error;
}