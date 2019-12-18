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
typedef  int u_int ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAXPATHLEN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int
check_luser(const char *luserdir, char *l_user)
{
	FILE	*f;
	int	 n;
	char	 tmp[MAXPATHLEN];

	n = snprintf(tmp, sizeof(tmp), "%s/%s", luserdir, l_user);
	if (n < 0 || (u_int)n >= sizeof(tmp)) {
		syslog(LOG_ERR, "provided banned directory line too long (%s)",
		    luserdir);
		return (0);
	}
	if ((f = fopen(tmp, "r")) == NULL) {
		if (errno == ENOENT) {
			/*
			 * file or dir doesn't exist, so therefore
			 * this luser isn't banned..  all is well
			 */
			return (1);
		} else {
			/*
			 * luser may in fact be banned, but we can't open the
			 * file even though it's there. probably a config
			 * problem.
			 */
			syslog(LOG_ERR, "cannot open banned file %s (%s)",
			    tmp, strerror(errno));
			return (0);
		}
	} else {
		/*
		 * luser is banned - spit the file at them to
		 * tell what they can do and where they can go.
		 */
		syslog(LOG_INFO, "denied access to %s: %s exists",
		    l_user, tmp);

		/* reuse tmp */
		strlcpy(tmp, "\n\n-**- Sorry, you have been banned! -**-\n\n",
		    sizeof(tmp));
		while (fputs(tmp, stdout) != EOF && !feof(f)) {
			if (fgets(tmp, sizeof(tmp), f) == NULL) {
				fflush(stdout);
				fclose(f);
				return (0);
			}
		}
		fclose(f);
	}
	fflush(stdout);
	return (0);
}