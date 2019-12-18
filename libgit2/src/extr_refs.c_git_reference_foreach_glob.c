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
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int (* git_reference_foreach_name_cb ) (char const*,void*) ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 
 int /*<<< orphan*/  git_reference_iterator_free (int /*<<< orphan*/ *) ; 
 int git_reference_iterator_glob_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int git_reference_next_name (char const**,int /*<<< orphan*/ *) ; 

int git_reference_foreach_glob(
	git_repository *repo,
	const char *glob,
	git_reference_foreach_name_cb callback,
	void *payload)
{
	git_reference_iterator *iter;
	const char *refname;
	int error;

	if ((error = git_reference_iterator_glob_new(&iter, repo, glob)) < 0)
		return error;

	while (!(error = git_reference_next_name(&refname, iter))) {
		if ((error = callback(refname, payload)) != 0) {
			git_error_set_after_callback(error);
			break;
		}
	}

	if (error == GIT_ITEROVER)
		error = 0;

	git_reference_iterator_free(iter);
	return error;
}