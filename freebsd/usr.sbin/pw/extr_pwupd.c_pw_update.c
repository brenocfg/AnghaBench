#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct passwd {int /*<<< orphan*/ * pw_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  etcpath; } ;

/* Variables and functions */
 struct passwd* GETPWNAM (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct passwd*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int pw_copy (int,int,struct passwd*,struct passwd*) ; 
 struct passwd* pw_dup (struct passwd*) ; 
 int /*<<< orphan*/  pw_fini () ; 
 scalar_t__ pw_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pw_lock () ; 
 int pw_mkdb (int /*<<< orphan*/ *) ; 
 int pw_tmp (int) ; 
 int pwdb_check () ; 

__attribute__((used)) static int
pw_update(struct passwd * pwd, char const * user)
{
	struct passwd	*pw = NULL;
	struct passwd	*old_pw = NULL;
	int		 rc, pfd, tfd;

	if ((rc = pwdb_check()) != 0)
		return (rc);

	if (pwd != NULL)
		pw = pw_dup(pwd);

	if (user != NULL)
		old_pw = GETPWNAM(user);

	if (pw_init(conf.etcpath, NULL))
		err(1, "pw_init()");
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
	/*
	 * in case of deletion of a user, the whole database
	 * needs to be regenerated
	 */
	if (pw_mkdb(pw != NULL ? pw->pw_name : NULL) == -1) {
		pw_fini();
		err(1, "pw_mkdb()");
	}
	free(pw);
	pw_fini();

	return (0);
}