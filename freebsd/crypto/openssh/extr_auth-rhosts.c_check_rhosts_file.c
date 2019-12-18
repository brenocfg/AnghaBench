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
typedef  int /*<<< orphan*/  userbuf ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int RBUFLN ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_debug_add (char*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  innetgr (char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logit (char*,char const*,char const*) ; 
 int open (char const*,int) ; 
 int sscanf (char*,char*,char*,char*,char*) ; 
 scalar_t__ strcasecmp (char*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  unset_nonblock (int) ; 

__attribute__((used)) static int
check_rhosts_file(const char *filename, const char *hostname,
		  const char *ipaddr, const char *client_user,
		  const char *server_user)
{
	FILE *f;
#define RBUFLN 1024
	char buf[RBUFLN];/* Must not be larger than host, user, dummy below. */
	int fd;
	struct stat st;

	/* Open the .rhosts file, deny if unreadable */
	if ((fd = open(filename, O_RDONLY|O_NONBLOCK)) == -1)
		return 0;
	if (fstat(fd, &st) == -1) {
		close(fd);
		return 0;
	}
	if (!S_ISREG(st.st_mode)) {
		logit("User %s hosts file %s is not a regular file",
		    server_user, filename);
		close(fd);
		return 0;
	}
	unset_nonblock(fd);
	if ((f = fdopen(fd, "r")) == NULL) {
		close(fd);
		return 0;
	}
	while (fgets(buf, sizeof(buf), f)) {
		/* All three must have length >= buf to avoid overflows. */
		char hostbuf[RBUFLN], userbuf[RBUFLN], dummy[RBUFLN];
		char *host, *user, *cp;
		int negated;

		for (cp = buf; *cp == ' ' || *cp == '\t'; cp++)
			;
		if (*cp == '#' || *cp == '\n' || !*cp)
			continue;

		/*
		 * NO_PLUS is supported at least on OSF/1.  We skip it (we
		 * don't ever support the plus syntax).
		 */
		if (strncmp(cp, "NO_PLUS", 7) == 0)
			continue;

		/*
		 * This should be safe because each buffer is as big as the
		 * whole string, and thus cannot be overwritten.
		 */
		switch (sscanf(buf, "%1023s %1023s %1023s", hostbuf, userbuf,
		    dummy)) {
		case 0:
			auth_debug_add("Found empty line in %.100s.", filename);
			continue;
		case 1:
			/* Host name only. */
			strlcpy(userbuf, server_user, sizeof(userbuf));
			break;
		case 2:
			/* Got both host and user name. */
			break;
		case 3:
			auth_debug_add("Found garbage in %.100s.", filename);
			continue;
		default:
			/* Weird... */
			continue;
		}

		host = hostbuf;
		user = userbuf;
		negated = 0;

		/* Process negated host names, or positive netgroups. */
		if (host[0] == '-') {
			negated = 1;
			host++;
		} else if (host[0] == '+')
			host++;

		if (user[0] == '-') {
			negated = 1;
			user++;
		} else if (user[0] == '+')
			user++;

		/* Check for empty host/user names (particularly '+'). */
		if (!host[0] || !user[0]) {
			/* We come here if either was '+' or '-'. */
			auth_debug_add("Ignoring wild host/user names "
			    "in %.100s.", filename);
			continue;
		}
		/* Verify that host name matches. */
		if (host[0] == '@') {
			if (!innetgr(host + 1, hostname, NULL, NULL) &&
			    !innetgr(host + 1, ipaddr, NULL, NULL))
				continue;
		} else if (strcasecmp(host, hostname) &&
		    strcmp(host, ipaddr) != 0)
			continue;	/* Different hostname. */

		/* Verify that user name matches. */
		if (user[0] == '@') {
			if (!innetgr(user + 1, NULL, client_user, NULL))
				continue;
		} else if (strcmp(user, client_user) != 0)
			continue;	/* Different username. */

		/* Found the user and host. */
		fclose(f);

		/* If the entry was negated, deny access. */
		if (negated) {
			auth_debug_add("Matched negative entry in %.100s.",
			    filename);
			return 0;
		}
		/* Accept authentication. */
		return 1;
	}

	/* Authentication using this file denied. */
	fclose(f);
	return 0;
}