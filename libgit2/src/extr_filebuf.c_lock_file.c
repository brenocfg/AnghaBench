#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {scalar_t__ fd; int fd_is_open; int /*<<< orphan*/  path_lock; int /*<<< orphan*/  path_original; int /*<<< orphan*/  digest; scalar_t__ compute_digest; } ;
typedef  TYPE_1__ git_filebuf ;
typedef  scalar_t__ git_file ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int FILEIO_BUFSIZE ; 
 int GIT_ELOCKED ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GIT_FILEBUF_APPEND ; 
 int GIT_FILEBUF_CREATE_LEADING_DIRS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_futils_creat_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_futils_creat_locked_withpath (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_close (scalar_t__) ; 
 scalar_t__ p_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ p_read (scalar_t__,char*,int) ; 
 int p_write (int,char*,scalar_t__) ; 

__attribute__((used)) static int lock_file(git_filebuf *file, int flags, mode_t mode)
{
	if (git_path_exists(file->path_lock) == true) {
		git_error_clear(); /* actual OS error code just confuses */
		git_error_set(GIT_ERROR_OS,
			"failed to lock file '%s' for writing", file->path_lock);
		return GIT_ELOCKED;
	}

	/* create path to the file buffer is required */
	if (flags & GIT_FILEBUF_CREATE_LEADING_DIRS) {
		/* XXX: Should dirmode here be configurable? Or is 0777 always fine? */
		file->fd = git_futils_creat_locked_withpath(file->path_lock, 0777, mode);
	} else {
		file->fd = git_futils_creat_locked(file->path_lock, mode);
	}

	if (file->fd < 0)
		return file->fd;

	file->fd_is_open = true;

	if ((flags & GIT_FILEBUF_APPEND) && git_path_exists(file->path_original) == true) {
		git_file source;
		char buffer[FILEIO_BUFSIZE];
		ssize_t read_bytes;
		int error = 0;

		source = p_open(file->path_original, O_RDONLY);
		if (source < 0) {
			git_error_set(GIT_ERROR_OS,
				"failed to open file '%s' for reading",
				file->path_original);
			return -1;
		}

		while ((read_bytes = p_read(source, buffer, sizeof(buffer))) > 0) {
			if ((error = p_write(file->fd, buffer, read_bytes)) < 0)
				break;
			if (file->compute_digest)
				git_hash_update(&file->digest, buffer, read_bytes);
		}

		p_close(source);

		if (read_bytes < 0) {
			git_error_set(GIT_ERROR_OS, "failed to read file '%s'", file->path_original);
			return -1;
		} else if (error < 0) {
			git_error_set(GIT_ERROR_OS, "failed to write file '%s'", file->path_lock);
			return -1;
		}
	}

	return 0;
}