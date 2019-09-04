#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_futils_mktmp (TYPE_1__*,char const*,int) ; 
 scalar_t__ p_close (int) ; 
 scalar_t__ p_lstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ p_symlink (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ p_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool are_symlinks_supported(const char *wd_path)
{
	git_config *config = NULL;
	git_buf global_buf = GIT_BUF_INIT;
	git_buf xdg_buf = GIT_BUF_INIT;
	git_buf system_buf = GIT_BUF_INIT;
	git_buf programdata_buf = GIT_BUF_INIT;
	git_buf path = GIT_BUF_INIT;
	int fd;
	struct stat st;
	int symlinks = 0;

	/*
	 * To emulate Git for Windows, symlinks on Windows must be explicitly
	 * opted-in.  We examine the system configuration for a core.symlinks
	 * set to true.  If found, we then examine the filesystem to see if
	 * symlinks are _actually_ supported by the current user.  If that is
	 * _not_ set, then we do not test or enable symlink support.
	 */
#ifdef GIT_WIN32
	git_config_find_global(&global_buf);
	git_config_find_xdg(&xdg_buf);
	git_config_find_system(&system_buf);
	git_config_find_programdata(&programdata_buf);

	if (load_config(&config, NULL,
	    path_unless_empty(&global_buf),
	    path_unless_empty(&xdg_buf),
	    path_unless_empty(&system_buf),
	    path_unless_empty(&programdata_buf)) < 0)
		goto done;

	if (git_config_get_bool(&symlinks, config, "core.symlinks") < 0 || !symlinks)
		goto done;
#endif

	if ((fd = git_futils_mktmp(&path, wd_path, 0666)) < 0 ||
	    p_close(fd) < 0 ||
	    p_unlink(path.ptr) < 0 ||
	    p_symlink("testing", path.ptr) < 0 ||
	    p_lstat(path.ptr, &st) < 0)
		goto done;

	symlinks = (S_ISLNK(st.st_mode) != 0);

	(void)p_unlink(path.ptr);

done:
	git_buf_dispose(&global_buf);
	git_buf_dispose(&xdg_buf);
	git_buf_dispose(&system_buf);
	git_buf_dispose(&programdata_buf);
	git_buf_dispose(&path);
	git_config_free(config);
	return symlinks != 0;
}