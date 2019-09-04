#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * _odb; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ODB_CAP_FROM_OWNER ; 
 int /*<<< orphan*/  GIT_REFCOUNT_OWN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_OBJECTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git__compare_and_swap (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_odb__add_default_backends (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_odb__set_caps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int git_odb_new (int /*<<< orphan*/ **) ; 
 int git_repository_item_path (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int git_repository_odb__weakptr(git_odb **out, git_repository *repo)
{
	int error = 0;

	assert(repo && out);

	if (repo->_odb == NULL) {
		git_buf odb_path = GIT_BUF_INIT;
		git_odb *odb;

		if ((error = git_repository_item_path(&odb_path, repo,
				GIT_REPOSITORY_ITEM_OBJECTS)) < 0 ||
			(error = git_odb_new(&odb)) < 0)
			return error;

		GIT_REFCOUNT_OWN(odb, repo);

		if ((error = git_odb__set_caps(odb, GIT_ODB_CAP_FROM_OWNER)) < 0 ||
			(error = git_odb__add_default_backends(odb, odb_path.ptr, 0, 0)) < 0) {
			git_odb_free(odb);
			return error;
		}

		odb = git__compare_and_swap(&repo->_odb, NULL, odb);
		if (odb != NULL) {
			GIT_REFCOUNT_OWN(odb, NULL);
			git_odb_free(odb);
		}

		git_buf_dispose(&odb_path);
	}

	*out = repo->_odb;
	return error;
}