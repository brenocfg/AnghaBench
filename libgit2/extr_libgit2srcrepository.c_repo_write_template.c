#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_UNUSED (int) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int p_write (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int repo_write_template(
	const char *git_dir,
	bool allow_overwrite,
	const char *file,
	mode_t mode,
	bool hidden,
	const char *content)
{
	git_buf path = GIT_BUF_INIT;
	int fd, error = 0, flags;

	if (git_buf_joinpath(&path, git_dir, file) < 0)
		return -1;

	if (allow_overwrite)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_EXCL;

	fd = p_open(git_buf_cstr(&path), flags, mode);

	if (fd >= 0) {
		error = p_write(fd, content, strlen(content));

		p_close(fd);
	}
	else if (errno != EEXIST)
		error = fd;

#ifdef GIT_WIN32
	if (!error && hidden) {
		if (git_win32__set_hidden(path.ptr, true) < 0)
			error = -1;
	}
#else
	GIT_UNUSED(hidden);
#endif

	git_buf_dispose(&path);

	if (error)
		git_error_set(GIT_ERROR_OS,
			"failed to initialize repository with template '%s'", file);

	return error;
}