#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int count; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  GIT_REFS_TAGS_DIR ; 
 int /*<<< orphan*/  GIT_SORT_TIME ; 
 int /*<<< orphan*/  git__prefixcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

__attribute__((used)) static int fetch_setup_walk(git_revwalk **out, git_repository *repo)
{
	git_revwalk *walk = NULL;
	git_strarray refs;
	unsigned int i;
	git_reference *ref = NULL;
	int error;

	if ((error = git_reference_list(&refs, repo)) < 0)
		return error;

	if ((error = git_revwalk_new(&walk, repo)) < 0)
		return error;

	git_revwalk_sorting(walk, GIT_SORT_TIME);

	for (i = 0; i < refs.count; ++i) {
		git_reference_free(ref);
		ref = NULL;

		/* No tags */
		if (!git__prefixcmp(refs.strings[i], GIT_REFS_TAGS_DIR))
			continue;

		if ((error = git_reference_lookup(&ref, repo, refs.strings[i])) < 0)
			goto on_error;

		if (git_reference_type(ref) == GIT_REFERENCE_SYMBOLIC)
			continue;

		if ((error = git_revwalk_push(walk, git_reference_target(ref))) < 0)
			goto on_error;
	}

	*out = walk;

on_error:
	if (error)
		git_revwalk_free(walk);
	git_reference_free(ref);
	git_strarray_free(&refs);
	return error;
}