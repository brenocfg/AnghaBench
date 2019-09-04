#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * _index; int /*<<< orphan*/  gitdir; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_INDEX_CAPABILITY_FROM_OWNER ; 
 int /*<<< orphan*/  GIT_INDEX_FILE ; 
 int /*<<< orphan*/  GIT_REFCOUNT_OWN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git__compare_and_swap (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_index_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_index_set_caps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_repository_index__weakptr(git_index **out, git_repository *repo)
{
	int error = 0;

	assert(out && repo);

	if (repo->_index == NULL) {
		git_buf index_path = GIT_BUF_INIT;
		git_index *index;

		if ((error = git_buf_joinpath(&index_path, repo->gitdir, GIT_INDEX_FILE)) < 0)
			return error;

		error = git_index_open(&index, index_path.ptr);
		if (!error) {
			GIT_REFCOUNT_OWN(index, repo);

			index = git__compare_and_swap(&repo->_index, NULL, index);
			if (index != NULL) {
				GIT_REFCOUNT_OWN(index, NULL);
				git_index_free(index);
			}

			error = git_index_set_caps(repo->_index,
			                           GIT_INDEX_CAPABILITY_FROM_OWNER);
		}

		git_buf_dispose(&index_path);
	}

	*out = repo->_index;
	return error;
}