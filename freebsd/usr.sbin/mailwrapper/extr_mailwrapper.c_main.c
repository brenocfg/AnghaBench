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
typedef  char* u_long ;
struct arglist {int /*<<< orphan*/  argv; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_MAIL ; 
 int /*<<< orphan*/  LOG_PID ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  WS ; 
 char* _PATH_DEFAULTMTA ; 
 char* _PATH_MAILERCONF ; 
 int /*<<< orphan*/  addarg (struct arglist*,char*) ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  execve (char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* fparseln (int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  initarg (struct arglist*) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strsep (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strspn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,char*) ; 

int
main(int argc, char *argv[], char *envp[])
{
	FILE *config;
	char *line, *cp, *from, *to, *ap;
	const char *progname;
	char localmailerconf[MAXPATHLEN];
	const char *mailerconf;
	size_t len, lineno = 0;
	int i;
	struct arglist al;

	/* change __progname to mailwrapper so we get sensible error messages */
	progname = getprogname();
	setprogname("mailwrapper");

	initarg(&al);
	addarg(&al, argv[0]);

	snprintf(localmailerconf, MAXPATHLEN, "%s/etc/mail/mailer.conf",
	    getenv("LOCALBASE") ? getenv("LOCALBASE") : "/usr/local");

	mailerconf = localmailerconf;
	if ((config = fopen(localmailerconf, "r")) == NULL)
		mailerconf = _PATH_MAILERCONF;

	if (config == NULL && ((config = fopen(mailerconf, "r")) == NULL)) {
		addarg(&al, NULL);
		openlog(getprogname(), LOG_PID, LOG_MAIL);
		syslog(LOG_INFO, "cannot open %s, using %s as default MTA",
		    mailerconf, _PATH_DEFAULTMTA);
		closelog();
		execve(_PATH_DEFAULTMTA, al.argv, envp);
		err(EX_OSERR, "cannot exec %s", _PATH_DEFAULTMTA);
		/*NOTREACHED*/
	}

	for (;;) {
		if ((line = fparseln(config, &len, &lineno, NULL, 0)) == NULL) {
			if (feof(config))
				errx(EX_CONFIG, "no mapping in %s", mailerconf);
			err(EX_CONFIG, "cannot parse line %lu", (u_long)lineno);
		}

#define	WS	" \t\n"
		cp = line;

		cp += strspn(cp, WS);
		if (cp[0] == '\0') {
			/* empty line */
			free(line);
			continue;
		}

		if ((from = strsep(&cp, WS)) == NULL || cp == NULL)
			goto parse_error;

		cp += strspn(cp, WS);

		if ((to = strsep(&cp, WS)) == NULL)
			goto parse_error;

		if (strcmp(from, progname) == 0) {
			for (ap = strsep(&cp, WS); ap != NULL;
			     ap = strsep(&cp, WS)) {
				if (*ap)
				    addarg(&al, ap);
			}
			break;
		}

		free(line);
	}

	(void)fclose(config);

	for (i = 1; i < argc; i++)
		addarg(&al, argv[i]);

	addarg(&al, NULL);
	execve(to, al.argv, envp);
	err(EX_OSERR, "cannot exec %s", to);
	/*NOTREACHED*/
parse_error:
	errx(EX_CONFIG, "parse error in %s at line %lu",
	    mailerconf, (u_long)lineno);
	/*NOTREACHED*/
}