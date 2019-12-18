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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  hname ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  NI_NAMEREQD ; 
 int __icheckhost (struct sockaddr const*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int innetgr (char*,char*,char const*,char*) ; 
 scalar_t__ isupper (unsigned char) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char tolower (unsigned char) ; 
 scalar_t__ yp_get_default_domain (char**) ; 

int
__ivaliduser_sa(FILE *hostf, const struct sockaddr *raddr, socklen_t salen,
    const char *luser, const char *ruser)
{
	char *user, *p;
	int ch;
	char buf[MAXHOSTNAMELEN + 128];		/* host + login */
	char hname[MAXHOSTNAMELEN];
	/* Presumed guilty until proven innocent. */
	int userok = 0, hostok = 0;
#ifdef YP
	char *ypdomain;

	if (yp_get_default_domain(&ypdomain))
		ypdomain = NULL;
#else
#define	ypdomain NULL
#endif
	/* We need to get the damn hostname back for netgroup matching. */
	if (getnameinfo(raddr, salen, hname, sizeof(hname), NULL, 0,
			NI_NAMEREQD) != 0)
		hname[0] = '\0';

	while (fgets(buf, sizeof(buf), hostf)) {
		p = buf;
		/* Skip lines that are too long. */
		if (strchr(p, '\n') == NULL) {
			while ((ch = getc(hostf)) != '\n' && ch != EOF);
			continue;
		}
		if (*p == '\n' || *p == '#') {
			/* comment... */
			continue;
		}
		while (*p != '\n' && *p != ' ' && *p != '\t' && *p != '\0') {
			*p = isupper((unsigned char)*p) ? tolower((unsigned char)*p) : *p;
			p++;
		}
		if (*p == ' ' || *p == '\t') {
			*p++ = '\0';
			while (*p == ' ' || *p == '\t')
				p++;
			user = p;
			while (*p != '\n' && *p != ' ' &&
			    *p != '\t' && *p != '\0')
				p++;
		} else
			user = p;
		*p = '\0';
		/*
		 * Do +/- and +@/-@ checking. This looks really nasty,
		 * but it matches SunOS's behavior so far as I can tell.
		 */
		switch(buf[0]) {
		case '+':
			if (!buf[1]) {     /* '+' matches all hosts */
				hostok = 1;
				break;
			}
			if (buf[1] == '@')  /* match a host by netgroup */
				hostok = hname[0] != '\0' &&
				    innetgr(&buf[2], hname, NULL, ypdomain);
			else		/* match a host by addr */
				hostok = __icheckhost(raddr, salen,
						      (char *)&buf[1]);
			break;
		case '-':     /* reject '-' hosts and all their users */
			if (buf[1] == '@') {
				if (hname[0] == '\0' ||
				    innetgr(&buf[2], hname, NULL, ypdomain))
					return(-1);
			} else {
				if (__icheckhost(raddr, salen,
						 (char *)&buf[1]))
					return(-1);
			}
			break;
		default:  /* if no '+' or '-', do a simple match */
			hostok = __icheckhost(raddr, salen, buf);
			break;
		}
		switch(*user) {
		case '+':
			if (!*(user+1)) {      /* '+' matches all users */
				userok = 1;
				break;
			}
			if (*(user+1) == '@')  /* match a user by netgroup */
				userok = innetgr(user+2, NULL, ruser, ypdomain);
			else	   /* match a user by direct specification */
				userok = !(strcmp(ruser, user+1));
			break;
		case '-': 		/* if we matched a hostname, */
			if (hostok) {   /* check for user field rejections */
				if (!*(user+1))
					return(-1);
				if (*(user+1) == '@') {
					if (innetgr(user+2, NULL,
							ruser, ypdomain))
						return(-1);
				} else {
					if (!strcmp(ruser, user+1))
						return(-1);
				}
			}
			break;
		default:	/* no rejections: try to match the user */
			if (hostok)
				userok = !(strcmp(ruser,*user ? user : luser));
			break;
		}
		if (hostok && userok)
			return(0);
	}
	return (-1);
}