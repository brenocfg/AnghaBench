#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_9__ {scalar_t__ key; } ;
typedef  TYPE_3__ git_attr_session ;
struct TYPE_8__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  stamp; } ;
struct TYPE_10__ {scalar_t__ session_key; int source; TYPE_2__ cache_data; TYPE_1__* entry; scalar_t__ nonexistent; } ;
typedef  TYPE_4__ git_attr_file ;
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/  fullpath; } ;

/* Variables and functions */
#define  GIT_ATTR_FILE__FROM_FILE 131 
#define  GIT_ATTR_FILE__FROM_HEAD 130 
#define  GIT_ATTR_FILE__FROM_INDEX 129 
#define  GIT_ATTR_FILE__IN_MEMORY 128 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int attr_file_oid_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int) ; 
 int git_futils_filestamp_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_oid__cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_tree_id (int /*<<< orphan*/ *) ; 

int git_attr_file__out_of_date(
	git_repository *repo,
	git_attr_session *attr_session,
	git_attr_file *file)
{
	if (!file)
		return 1;

	/* we are never out of date if we just created this data in the same
	 * attr_session; otherwise, nonexistent files must be invalidated
	 */
	if (attr_session && attr_session->key == file->session_key)
		return 0;
	else if (file->nonexistent)
		return 1;

	switch (file->source) {
	case GIT_ATTR_FILE__IN_MEMORY:
		return 0;

	case GIT_ATTR_FILE__FROM_FILE:
		return git_futils_filestamp_check(
			&file->cache_data.stamp, file->entry->fullpath);

	case GIT_ATTR_FILE__FROM_INDEX: {
		int error;
		git_oid id;

		if ((error = attr_file_oid_from_index(
				&id, repo, file->entry->path)) < 0)
			return error;

		return (git_oid__cmp(&file->cache_data.oid, &id) != 0);
	}

	case GIT_ATTR_FILE__FROM_HEAD: {
		git_tree *tree;
		int error;

		if ((error = git_repository_head_tree(&tree, repo)) < 0)
			return error;

		error = git_oid__cmp(&file->cache_data.oid, git_tree_id(tree));

		git_tree_free(tree);
		return error;
	}

	default:
		git_error_set(GIT_ERROR_INVALID, "invalid file type %d", file->source);
		return -1;
	}
}