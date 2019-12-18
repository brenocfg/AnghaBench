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
typedef  int /*<<< orphan*/  u_long ;
struct hostent {int /*<<< orphan*/  h_name; } ;
typedef  int /*<<< orphan*/  hname ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EOF ; 
 int MaxHostNameLen ; 
 int __icheckhost (unsigned int,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 int innetgr (char*,char*,char*,char*) ; 
 scalar_t__ isupper (unsigned char) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 char tolower (unsigned char) ; 
 scalar_t__ yp_get_default_domain (char**) ; 

__attribute__((used)) static
int
__ivaliduser(FILE *hostf, unsigned raddr, const char *luser,
	     const char *ruser)
{
	char *user, *p;
	int ch;
	char buf[MaxHostNameLen + 128];		/* host + login */
	char hname[MaxHostNameLen];
	struct hostent *hp;
	/* Presumed guilty until proven innocent. */
	int userok = 0, hostok = 0;
#ifdef HAVE_YP_GET_DEFAULT_DOMAIN
	char *ypdomain;

	if (yp_get_default_domain(&ypdomain))
		ypdomain = NULL;
#else
#define	ypdomain NULL
#endif
	/* We need to get the damn hostname back for netgroup matching. */
	if ((hp = gethostbyaddr((char *)&raddr,
				sizeof(u_long),
				AF_INET)) == NULL)
		return (-1);
	strlcpy(hname, hp->h_name, sizeof(hname));

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
		        if (isupper((unsigned char)*p))
			    *p = tolower((unsigned char)*p);
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
				hostok = innetgr((char *)&buf[2],
					(char *)&hname, NULL, ypdomain);
			else		/* match a host by addr */
				hostok = __icheckhost(raddr,(char *)&buf[1]);
			break;
		case '-':     /* reject '-' hosts and all their users */
			if (buf[1] == '@') {
				if (innetgr((char *)&buf[2],
					      (char *)&hname, NULL, ypdomain))
					return(-1);
			} else {
				if (__icheckhost(raddr,(char *)&buf[1]))
					return(-1);
			}
			break;
		default:  /* if no '+' or '-', do a simple match */
			hostok = __icheckhost(raddr, buf);
			break;
		}
		switch(*user) {
		case '+':
			if (!*(user+1)) {      /* '+' matches all users */
				userok = 1;
				break;
			}
			if (*(user+1) == '@')  /* match a user by netgroup */
				userok = innetgr(user+2, NULL, (char *)ruser,
						 ypdomain);
			else	   /* match a user by direct specification */
				userok = !(strcmp(ruser, user+1));
			break;
		case '-': 		/* if we matched a hostname, */
			if (hostok) {   /* check for user field rejections */
				if (!*(user+1))
					return(-1);
				if (*(user+1) == '@') {
					if (innetgr(user+2, NULL,
						    (char *)ruser, ypdomain))
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