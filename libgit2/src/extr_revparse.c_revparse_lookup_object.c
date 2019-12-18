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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_reference_dwim (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int maybe_abbrev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int maybe_describe (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int maybe_sha (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int revparse_lookup_object(
	git_object **object_out,
	git_reference **reference_out,
	git_repository *repo,
	const char *spec)
{
	int error;
	git_reference *ref;

	if ((error = maybe_sha(object_out, repo, spec)) != GIT_ENOTFOUND)
		return error;

	error = git_reference_dwim(&ref, repo, spec);
	if (!error) {

		error = git_object_lookup(
			object_out, repo, git_reference_target(ref), GIT_OBJECT_ANY);

		if (!error)
			*reference_out = ref;

		return error;
	}

	if (error != GIT_ENOTFOUND)
		return error;

	if ((strlen(spec) < GIT_OID_HEXSZ) &&
		((error = maybe_abbrev(object_out, repo, spec)) != GIT_ENOTFOUND))
			return error;

	if ((error = maybe_describe(object_out, repo, spec)) != GIT_ENOTFOUND)
		return error;

	git_error_set(GIT_ERROR_REFERENCE, "revspec '%s' not found", spec);
	return GIT_ENOTFOUND;
}