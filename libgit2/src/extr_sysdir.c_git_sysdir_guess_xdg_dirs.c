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
typedef  scalar_t__ uid_t ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int get_passwd_home (TYPE_1__*,scalar_t__) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 int git__getenv (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_win32__find_xdg_dirs (TYPE_1__*) ; 

__attribute__((used)) static int git_sysdir_guess_xdg_dirs(git_buf *out)
{
#ifdef GIT_WIN32
	return git_win32__find_xdg_dirs(out);
#else
	git_buf env = GIT_BUF_INIT;
	int error;
	uid_t uid, euid;

	uid = getuid();
	euid = geteuid();

	/*
	 * In case we are running setuid, only look up passwd
	 * directory of the effective user.
	 */
	if (uid == euid) {
		if ((error = git__getenv(&env, "XDG_CONFIG_HOME")) == 0)
			error = git_buf_joinpath(out, env.ptr, "git");

		if (error == GIT_ENOTFOUND && (error = git__getenv(&env, "HOME")) == 0)
			error = git_buf_joinpath(out, env.ptr, ".config/git");
	} else {
		if ((error = get_passwd_home(&env, euid)) == 0)
			error = git_buf_joinpath(out, env.ptr, ".config/git");
	}

	if (error == GIT_ENOTFOUND) {
		git_error_clear();
		error = 0;
	}

	git_buf_dispose(&env);
	return error;
#endif
}