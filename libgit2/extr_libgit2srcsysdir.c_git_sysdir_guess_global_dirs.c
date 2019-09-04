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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int get_passwd_home (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 int git__getenv (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_error_clear () ; 

__attribute__((used)) static int git_sysdir_guess_global_dirs(git_buf *out)
{
#ifdef GIT_WIN32
	return git_win32__find_global_dirs(out);
#else
	int error;
	uid_t uid, euid;

	uid = getuid();
	euid = geteuid();

	/*
	 * In case we are running setuid, use the configuration
	 * of the effective user.
	 */
	if (uid == euid)
	    error = git__getenv(out, "HOME");
	else
	    error = get_passwd_home(out, euid);

	if (error == GIT_ENOTFOUND) {
		git_error_clear();
		error = 0;
	}

	return error;
#endif
}