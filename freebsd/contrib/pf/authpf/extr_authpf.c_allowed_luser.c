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
struct passwd {char* pw_class; char* pw_name; int /*<<< orphan*/  pw_gid; } ;
struct group {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int NGROUPS ; 
 char* PATH_ALLOWFILE ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct group* getgrnam (char*) ; 
 int /*<<< orphan*/  getgrouplist (char*,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,char*,...) ; 

__attribute__((used)) static int
allowed_luser(struct passwd *pw)
{
	char *buf,*lbuf;
	int	 matched;
	size_t	 len;
	FILE	*f;

	if ((f = fopen(PATH_ALLOWFILE, "r")) == NULL) {
		if (errno == ENOENT) {
			/*
			 * allowfile doesn't exist, thus this gateway
			 * isn't restricted to certain users...
			 */
			return (1);
		}

		/*
		 * luser may in fact be allowed, but we can't open
		 * the file even though it's there. probably a config
		 * problem.
		 */
		syslog(LOG_ERR, "cannot open allowed users file %s (%s)",
		    PATH_ALLOWFILE, strerror(errno));
		return (0);
	} else {
		/*
		 * /etc/authpf/authpf.allow exists, thus we do a linear
		 * search to see if they are allowed.
		 * also, if username "*" exists, then this is a
		 * "public" gateway, such as it is, so let
		 * everyone use it.
		 */
		int gl_init = 0, ngroups = NGROUPS + 1;
		gid_t groups[NGROUPS + 1];

		lbuf = NULL;
		matched = 0;

		while ((buf = fgetln(f, &len))) {
			
			if (buf[len - 1] == '\n')
				buf[len - 1] = '\0';
			else {
				if ((lbuf = (char *)malloc(len + 1)) == NULL)
					err(1, NULL);
				memcpy(lbuf, buf, len);
				lbuf[len] = '\0';
				buf = lbuf;
			}

			if (buf[0] == '@') {
				/* check login class */
				if (strcmp(pw->pw_class, buf + 1) == 0)
					matched++;
			} else if (buf[0] == '%') {
				/* check group membership */
				int cnt; 
				struct group *group;

				if ((group = getgrnam(buf + 1)) == NULL) {
					syslog(LOG_ERR,
					    "invalid group '%s' in %s (%s)",
					    buf + 1, PATH_ALLOWFILE,
				 	    strerror(errno));
					return (0);
				}

				if (!gl_init) {
					(void) getgrouplist(pw->pw_name,
					    pw->pw_gid, groups, &ngroups);
					gl_init++;
				}
			
				for ( cnt = 0; cnt < ngroups; cnt++) {
					if (group->gr_gid == groups[cnt]) {
						matched++;
						break;
					}
				}
			} else {
				/* check username and wildcard */
				matched = strcmp(pw->pw_name, buf) == 0 ||
				    strcmp("*", buf) == 0;
			}

			if (lbuf != NULL) {
				free(lbuf);
				lbuf = NULL;
			}

			if (matched)
				return (1); /* matched an allowed user/group */
		}
		syslog(LOG_INFO, "denied access to %s: not listed in %s",
		    pw->pw_name, PATH_ALLOWFILE);

		/* reuse buf */
		sprintf(buf, "%s", "\n\nSorry, you are not allowed to use this facility!\n");
		fputs(buf, stdout);
	}
	fflush(stdout);
	return (0);
}