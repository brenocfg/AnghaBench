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
typedef  int /*<<< orphan*/  git_blame_options ;
typedef  int /*<<< orphan*/  git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BLAME_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int blame_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_blame__alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_blame_free (int /*<<< orphan*/ *) ; 
 int load_blob (int /*<<< orphan*/ *) ; 
 int normalize_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_blame_file(
		git_blame **out,
		git_repository *repo,
		const char *path,
		git_blame_options *options)
{
	int error = -1;
	git_blame_options normOptions = GIT_BLAME_OPTIONS_INIT;
	git_blame *blame = NULL;

	assert(out && repo && path);
	if ((error = normalize_options(&normOptions, options, repo)) < 0)
		goto on_error;

	blame = git_blame__alloc(repo, normOptions, path);
	GIT_ERROR_CHECK_ALLOC(blame);

	if ((error = load_blob(blame)) < 0)
		goto on_error;

	if ((error = blame_internal(blame)) < 0)
		goto on_error;

	*out = blame;
	return 0;

on_error:
	git_blame_free(blame);
	return error;
}