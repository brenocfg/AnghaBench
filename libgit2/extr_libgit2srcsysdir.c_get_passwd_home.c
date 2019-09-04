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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_dir; } ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  _SC_GETPW_R_SIZE_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,long,struct passwd**) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__realloc (char*,long) ; 
 int git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_passwd_home(git_buf *out, uid_t uid)
{
	struct passwd pwd, *pwdptr;
	char *buf = NULL;
	long buflen;
	int error;

	assert(out);

	if ((buflen = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1)
		buflen = 1024;

	do {
		buf = git__realloc(buf, buflen);
		error = getpwuid_r(uid, &pwd, buf, buflen, &pwdptr);
		buflen *= 2;
	} while (error == ERANGE && buflen <= 8192);

	if (error) {
		git_error_set(GIT_ERROR_OS, "failed to get passwd entry");
		goto out;
	}

	if (!pwdptr) {
		git_error_set(GIT_ERROR_OS, "no passwd entry found for user");
		goto out;
	}

	if ((error = git_buf_puts(out, pwdptr->pw_dir)) < 0)
		goto out;

out:
	git__free(buf);
	return error;
}