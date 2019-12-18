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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_regexp ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_SORT_TIME ; 
 int build_regex (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int git_revwalk_push_glob (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int walk_and_search (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_grep_syntax(git_object **out, git_repository *repo, const git_oid *spec_oid, const char *pattern)
{
	git_regexp preg;
	git_revwalk *walk = NULL;
	int error;

	if ((error = build_regex(&preg, pattern)) < 0)
		return error;

	if ((error = git_revwalk_new(&walk, repo)) < 0)
		goto cleanup;

	git_revwalk_sorting(walk, GIT_SORT_TIME);

	if (spec_oid == NULL) {
		if ((error = git_revwalk_push_glob(walk, "refs/*")) < 0)
			goto cleanup;
	} else if ((error = git_revwalk_push(walk, spec_oid)) < 0)
			goto cleanup;

	error = walk_and_search(out, walk, &preg);

cleanup:
	git_regexp_dispose(&preg);
	git_revwalk_free(walk);

	return error;
}