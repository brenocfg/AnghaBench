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
struct stat {int dummy; } ;
struct passwd {scalar_t__ pw_uid; int /*<<< orphan*/  pw_name; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _PATH_NOLOGIN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lc ; 
 scalar_t__ login_getcapbool (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* login_getcapstr (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  logit (char*,int /*<<< orphan*/ ,char const*) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
do_nologin(struct passwd *pw)
{
	FILE *f = NULL;
	const char *nl;
	char buf[1024], *def_nl = _PATH_NOLOGIN;
	struct stat sb;

#ifdef HAVE_LOGIN_CAP
	if (login_getcapbool(lc, "ignorenologin", 0) || pw->pw_uid == 0)
		return;
	nl = login_getcapstr(lc, "nologin", def_nl, def_nl);
#else
	if (pw->pw_uid == 0)
		return;
	nl = def_nl;
#endif
	if (stat(nl, &sb) == -1)
		return;

	/* /etc/nologin exists.  Print its contents if we can and exit. */
	logit("User %.100s not allowed because %s exists", pw->pw_name, nl);
	if ((f = fopen(nl, "r")) != NULL) {
		while (fgets(buf, sizeof(buf), f))
			fputs(buf, stderr);
		fclose(f);
	}
	exit(254);
}