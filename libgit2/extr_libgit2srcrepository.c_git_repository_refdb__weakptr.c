#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * _refdb; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_OWN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git__compare_and_swap (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 
 int git_refdb_open (int /*<<< orphan*/ **,TYPE_1__*) ; 

int git_repository_refdb__weakptr(git_refdb **out, git_repository *repo)
{
	int error = 0;

	assert(out && repo);

	if (repo->_refdb == NULL) {
		git_refdb *refdb;

		error = git_refdb_open(&refdb, repo);
		if (!error) {
			GIT_REFCOUNT_OWN(refdb, repo);

			refdb = git__compare_and_swap(&repo->_refdb, NULL, refdb);
			if (refdb != NULL) {
				GIT_REFCOUNT_OWN(refdb, NULL);
				git_refdb_free(refdb);
			}
		}
	}

	*out = repo->_refdb;
	return error;
}