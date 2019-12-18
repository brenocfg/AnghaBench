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
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECKOUT ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_OWN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_checkout_iterator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_owner (int /*<<< orphan*/ *) ; 
 int git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_checkout_index(
	git_repository *repo,
	git_index *index,
	const git_checkout_options *opts)
{
	int error, owned = 0;
	git_iterator *index_i;

	if (!index && !repo) {
		git_error_set(GIT_ERROR_CHECKOUT,
			"must provide either repository or index to checkout");
		return -1;
	}

	if (index && repo &&
		git_index_owner(index) &&
		git_index_owner(index) != repo) {
		git_error_set(GIT_ERROR_CHECKOUT,
			"index to checkout does not match repository");
		return -1;
	} else if(index && repo && !git_index_owner(index)) {
		GIT_REFCOUNT_OWN(index, repo);
		owned = 1;
	}

	if (!repo)
		repo = git_index_owner(index);

	if (!index && (error = git_repository_index__weakptr(&index, repo)) < 0)
		return error;
	GIT_REFCOUNT_INC(index);

	if (!(error = git_iterator_for_index(&index_i, repo, index, NULL)))
		error = git_checkout_iterator(index_i, index, opts);

	if (owned)
		GIT_REFCOUNT_OWN(index, NULL);

	git_iterator_free(index_i);
	git_index_free(index);

	return error;
}