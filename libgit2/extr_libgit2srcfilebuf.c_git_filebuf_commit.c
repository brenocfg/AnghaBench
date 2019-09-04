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
struct TYPE_6__ {int fd_is_open; int fd; int did_rename; scalar_t__ path_original; scalar_t__ do_fsync; scalar_t__ path_lock; int /*<<< orphan*/  flush_mode; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flush_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (TYPE_1__*) ; 
 scalar_t__ git_futils_fsync_parent (scalar_t__) ; 
 scalar_t__ p_close (int) ; 
 scalar_t__ p_fsync (int) ; 
 scalar_t__ p_rename (scalar_t__,scalar_t__) ; 
 scalar_t__ verify_last_error (TYPE_1__*) ; 

int git_filebuf_commit(git_filebuf *file)
{
	/* temporary files cannot be committed */
	assert(file && file->path_original);

	file->flush_mode = Z_FINISH;
	flush_buffer(file);

	if (verify_last_error(file) < 0)
		goto on_error;

	file->fd_is_open = false;

	if (file->do_fsync && p_fsync(file->fd) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to fsync '%s'", file->path_lock);
		goto on_error;
	}

	if (p_close(file->fd) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to close file at '%s'", file->path_lock);
		goto on_error;
	}

	file->fd = -1;

	if (p_rename(file->path_lock, file->path_original) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to rename lockfile to '%s'", file->path_original);
		goto on_error;
	}

	if (file->do_fsync && git_futils_fsync_parent(file->path_original) < 0)
		goto on_error;

	file->did_rename = true;

	git_filebuf_cleanup(file);
	return 0;

on_error:
	git_filebuf_cleanup(file);
	return -1;
}