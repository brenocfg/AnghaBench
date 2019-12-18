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
struct passwd {int dummy; } ;

/* Variables and functions */
 struct passwd* GETPWNAM (char const*) ; 
 int chmod (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct passwd*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int pw_copy (int,int,struct passwd*,struct passwd*) ; 
 struct passwd* pw_dup (struct passwd*) ; 
 int /*<<< orphan*/  pw_fini () ; 
 scalar_t__ pw_init (int /*<<< orphan*/ *,char const*) ; 
 int pw_lock () ; 
 int /*<<< orphan*/  pw_tempname () ; 
 int pw_tmp (int) ; 
 int rename (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
pw_nisupdate(const char * path, struct passwd * pwd, char const * user)
{
	int pfd, tfd;
	struct passwd *pw = NULL;
	struct passwd *old_pw = NULL;

	printf("===> %s\n", path);
	if (pwd != NULL)
		pw = pw_dup(pwd);

	if (user != NULL)
		old_pw = GETPWNAM(user);

	if (pw_init(NULL, path))
		err(1,"pw_init()");
	if ((pfd = pw_lock()) == -1) {
		pw_fini();
		err(1, "pw_lock()");
	}
	if ((tfd = pw_tmp(-1)) == -1) {
		pw_fini();
		err(1, "pw_tmp()");
	}
	if (pw_copy(pfd, tfd, pw, old_pw) == -1) {
		pw_fini();
		close(tfd);
		err(1, "pw_copy()");
	}
	fsync(tfd);
	close(tfd);
	if (chmod(pw_tempname(), 0644) == -1)
		err(1, "chmod()");
	if (rename(pw_tempname(), path) == -1)
		err(1, "rename()");

	free(pw);
	pw_fini();

	return (0);
}