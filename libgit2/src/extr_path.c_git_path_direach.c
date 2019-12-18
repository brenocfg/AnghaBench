#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  git_path_iconv_t ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GIT_PATH_DIR_PRECOMPOSE_UNICODE ; 
 int /*<<< orphan*/  GIT_PATH_ICONV_INIT ; 
 int /*<<< orphan*/  GIT_UNUSED (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_len (TYPE_1__*) ; 
 int git_buf_put (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_last () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set_after_callback (int) ; 
 int git_path_iconv (int /*<<< orphan*/ *,char const**,size_t*) ; 
 int /*<<< orphan*/  git_path_iconv_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_iconv_init_precompose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_path_is_dot_or_dotdot (char const*) ; 
 scalar_t__ git_path_to_dir (TYPE_1__*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

int git_path_direach(
	git_buf *path,
	uint32_t flags,
	int (*fn)(void *, git_buf *),
	void *arg)
{
	int error = 0;
	ssize_t wd_len;
	DIR *dir;
	struct dirent *de;

#ifdef GIT_USE_ICONV
	git_path_iconv_t ic = GIT_PATH_ICONV_INIT;
#endif

	GIT_UNUSED(flags);

	if (git_path_to_dir(path) < 0)
		return -1;

	wd_len = git_buf_len(path);

	if ((dir = opendir(path->ptr)) == NULL) {
		git_error_set(GIT_ERROR_OS, "failed to open directory '%s'", path->ptr);
		if (errno == ENOENT)
			return GIT_ENOTFOUND;

		return -1;
	}

#ifdef GIT_USE_ICONV
	if ((flags & GIT_PATH_DIR_PRECOMPOSE_UNICODE) != 0)
		(void)git_path_iconv_init_precompose(&ic);
#endif

	while ((de = readdir(dir)) != NULL) {
		const char *de_path = de->d_name;
		size_t de_len = strlen(de_path);

		if (git_path_is_dot_or_dotdot(de_path))
			continue;

#ifdef GIT_USE_ICONV
		if ((error = git_path_iconv(&ic, &de_path, &de_len)) < 0)
			break;
#endif

		if ((error = git_buf_put(path, de_path, de_len)) < 0)
			break;

		git_error_clear();
		error = fn(arg, path);

		git_buf_truncate(path, wd_len); /* restore path */

		/* Only set our own error if the callback did not set one already */
		if (error != 0) {
			if (!git_error_last())
				git_error_set_after_callback(error);

			break;
		}
	}

	closedir(dir);

#ifdef GIT_USE_ICONV
	git_path_iconv_clear(&ic);
#endif

	return error;
}