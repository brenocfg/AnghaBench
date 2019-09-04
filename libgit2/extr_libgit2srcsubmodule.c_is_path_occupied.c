#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_sets (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_index_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int git_index_find_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_path_to_dir (TYPE_1__*) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_path_occupied(bool *occupied, git_repository *repo, const char *path)
{
	int error = 0;
	git_index *index;
	git_buf dir = GIT_BUF_INIT;
	*occupied = false;

	if ((error = git_repository_index__weakptr(&index, repo)) < 0)
		goto out;

	if ((error = git_index_find(NULL, index, path)) != GIT_ENOTFOUND) {
		if (!error) {
			git_error_set(GIT_ERROR_SUBMODULE,
				"File '%s' already exists in the index", path);
			*occupied = true;
		}
		goto out;
	}

	if ((error = git_buf_sets(&dir, path)) < 0)
		goto out;

	if ((error = git_path_to_dir(&dir)) < 0)
		goto out;

	if ((error = git_index_find_prefix(NULL, index, dir.ptr)) != GIT_ENOTFOUND) {
		if (!error) {
			git_error_set(GIT_ERROR_SUBMODULE,
				"Directory '%s' already exists in the index", path);
			*occupied = true;
		}
		goto out;
	}

	error = 0;

out:
	git_buf_dispose(&dir);
	return error;
}