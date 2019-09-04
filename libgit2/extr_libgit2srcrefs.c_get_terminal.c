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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int MAX_NESTING_LEVEL ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 char* git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_terminal(git_reference **out, git_repository *repo, const char *ref_name, int nesting)
{
	git_reference *ref;
	int error = 0;

	if (nesting > MAX_NESTING_LEVEL) {
		git_error_set(GIT_ERROR_REFERENCE, "reference chain too deep (%d)", nesting);
		return GIT_ENOTFOUND;
	}

	/* set to NULL to let the caller know that they're at the end of the chain */
	if ((error = git_reference_lookup(&ref, repo, ref_name)) < 0) {
		*out = NULL;
		return error;
	}

	if (git_reference_type(ref) == GIT_REFERENCE_DIRECT) {
		*out = ref;
		error = 0;
	} else {
		error = get_terminal(out, repo, git_reference_symbolic_target(ref), nesting + 1);
		if (error == GIT_ENOTFOUND && !*out)
			*out = ref;
		else
			git_reference_free(ref);
	}

	return error;
}