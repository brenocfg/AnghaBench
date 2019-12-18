#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* gitpath; char* commonpath; scalar_t__ fsync; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_EDIRECTORY ; 
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int GIT_FILEBUF_CREATE_LEADING_DIRS ; 
 int GIT_FILEBUF_FSYNC ; 
 int /*<<< orphan*/  GIT_PATH_REJECT_FILESYSTEM_DEFAULTS ; 
 int /*<<< orphan*/  GIT_REFS_FILE_MODE ; 
 int /*<<< orphan*/  GIT_RMDIR_SKIP_NONEMPTY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int git_futils_rmdir_r (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isvalid (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_per_worktree_ref (char const*) ; 

__attribute__((used)) static int loose_lock(git_filebuf *file, refdb_fs_backend *backend, const char *name)
{
	int error, filebuf_flags;
	git_buf ref_path = GIT_BUF_INIT;
	const char *basedir;

	assert(file && backend && name);

	if (!git_path_isvalid(backend->repo, name, 0, GIT_PATH_REJECT_FILESYSTEM_DEFAULTS)) {
		git_error_set(GIT_ERROR_INVALID, "invalid reference name '%s'", name);
		return GIT_EINVALIDSPEC;
	}

	if (is_per_worktree_ref(name))
		basedir = backend->gitpath;
	else
		basedir = backend->commonpath;

	/* Remove a possibly existing empty directory hierarchy
	 * which name would collide with the reference name
	 */
	if ((error = git_futils_rmdir_r(name, basedir, GIT_RMDIR_SKIP_NONEMPTY)) < 0)
		return error;

	if (git_buf_joinpath(&ref_path, basedir, name) < 0)
		return -1;

	filebuf_flags = GIT_FILEBUF_CREATE_LEADING_DIRS;
	if (backend->fsync)
		filebuf_flags |= GIT_FILEBUF_FSYNC;

	error = git_filebuf_open(file, ref_path.ptr, filebuf_flags, GIT_REFS_FILE_MODE);

	if (error == GIT_EDIRECTORY)
		git_error_set(GIT_ERROR_REFERENCE, "cannot lock ref '%s', there are refs beneath that folder", name);

	git_buf_dispose(&ref_path);
	return error;
}