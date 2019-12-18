#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ dirty; int /*<<< orphan*/  stamp; int /*<<< orphan*/  tree_pool; int /*<<< orphan*/ * tree; int /*<<< orphan*/  index_file_path; int /*<<< orphan*/  on_disk; } ;
typedef  TYPE_1__ git_index ;
typedef  int /*<<< orphan*/  git_futils_filestamp ;
struct TYPE_11__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int compare_checksum (TYPE_1__*) ; 
 int create_index_error (int,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_futils_filestamp_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_filestamp_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_futils_readbuffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int git_index_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int parse_index (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_index_read(git_index *index, int force)
{
	int error = 0, updated;
	git_buf buffer = GIT_BUF_INIT;
	git_futils_filestamp stamp = index->stamp;

	if (!index->index_file_path)
		return create_index_error(-1,
			"failed to read index: The index is in-memory only");

	index->on_disk = git_path_exists(index->index_file_path);

	if (!index->on_disk) {
		if (force && (error = git_index_clear(index)) < 0)
			return error;

		index->dirty = 0;
		return 0;
	}

	if ((updated = git_futils_filestamp_check(&stamp, index->index_file_path) < 0) ||
	    ((updated = compare_checksum(index)) < 0)) {
		git_error_set(
			GIT_ERROR_INDEX,
			"failed to read index: '%s' no longer exists",
			index->index_file_path);
		return updated;
	}

	if (!updated && !force)
		return 0;

	error = git_futils_readbuffer(&buffer, index->index_file_path);
	if (error < 0)
		return error;

	index->tree = NULL;
	git_pool_clear(&index->tree_pool);

	error = git_index_clear(index);

	if (!error)
		error = parse_index(index, buffer.ptr, buffer.size);

	if (!error) {
		git_futils_filestamp_set(&index->stamp, &stamp);
		index->dirty = 0;
	}

	git_buf_dispose(&buffer);
	return error;
}