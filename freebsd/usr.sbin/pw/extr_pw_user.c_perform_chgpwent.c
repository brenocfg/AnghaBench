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
struct passwd {int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_IOERR ; 
 int chgnispwent (char*,char const*,struct passwd*) ; 
 int chgpwent (char const*,struct passwd*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct passwd* pw_dup (struct passwd*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static void
perform_chgpwent(const char *name, struct passwd *pwd, char *nispasswd)
{
	int rc;
	struct passwd *nispwd;

	/* duplicate for nis so that chgpwent is not modifying before NIS */
	if (nispasswd && *nispasswd == '/')
		nispwd = pw_dup(pwd);

	rc = chgpwent(name, pwd);
	if (rc == -1)
		errx(EX_IOERR, "user '%s' does not exist (NIS?)", pwd->pw_name);
	else if (rc != 0)
		err(EX_IOERR, "passwd file update");

	if (nispasswd && *nispasswd == '/') {
		rc = chgnispwent(nispasswd, name, nispwd);
		if (rc == -1)
			warn("User '%s' not found in NIS passwd", pwd->pw_name);
		else if (rc != 0)
			warn("NIS passwd update");
		/* NOTE: NIS-only update errors are not fatal */
	}
}