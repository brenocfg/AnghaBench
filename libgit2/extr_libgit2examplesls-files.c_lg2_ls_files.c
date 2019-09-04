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
typedef  int /*<<< orphan*/  ls_options ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int parse_options (int /*<<< orphan*/ *,int,char**) ; 
 int print_paths (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int lg2_ls_files(git_repository *repo, int argc, char *argv[])
{
	git_index *index = NULL;
	ls_options opts;
	int error;

	if ((error = parse_options(&opts, argc, argv)) < 0)
		return error;

	if ((error = git_repository_index(&index, repo)) < 0)
		goto cleanup;

	error = print_paths(&opts, index);

cleanup:
	git_index_free(index);

	return error;
}