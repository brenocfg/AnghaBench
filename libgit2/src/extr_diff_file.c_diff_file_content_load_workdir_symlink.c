#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_2__ map; TYPE_1__* file; int /*<<< orphan*/  flags; int /*<<< orphan*/  repo; } ;
typedef  TYPE_3__ git_diff_file_content ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_6__ {int size; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_SYMLINKS ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__FREE_DATA ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int diff_file_content_load_workdir_symlink_fake (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int git_repository__configmap_lookup (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ p_readlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int diff_file_content_load_workdir_symlink(
	git_diff_file_content *fc, git_buf *path)
{
	ssize_t alloc_len, read_len;
	int symlink_supported, error;

	if ((error = git_repository__configmap_lookup(
		&symlink_supported, fc->repo, GIT_CONFIGMAP_SYMLINKS)) < 0)
		return -1;

	if (!symlink_supported)
		return diff_file_content_load_workdir_symlink_fake(fc, path);

	/* link path on disk could be UTF-16, so prepare a buffer that is
	 * big enough to handle some UTF-8 data expansion
	 */
	alloc_len = (ssize_t)(fc->file->size * 2) + 1;

	fc->map.data = git__calloc(alloc_len, sizeof(char));
	GIT_ERROR_CHECK_ALLOC(fc->map.data);

	fc->flags |= GIT_DIFF_FLAG__FREE_DATA;

	read_len = p_readlink(git_buf_cstr(path), fc->map.data, alloc_len);
	if (read_len < 0) {
		git_error_set(GIT_ERROR_OS, "failed to read symlink '%s'", fc->file->path);
		return -1;
	}

	fc->map.len = read_len;
	return 0;
}