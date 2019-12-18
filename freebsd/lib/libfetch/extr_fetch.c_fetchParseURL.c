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
struct url {int netrcfd; char* scheme; char* host; int port; char* doc; int /*<<< orphan*/  pwd; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*) ; 
 int INT_MAX ; 
 int IPPORT_MAX ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  SCHEME_HTTP ; 
 int /*<<< orphan*/  SCHEME_HTTPS ; 
 int /*<<< orphan*/  URL_BAD_PORT ; 
 int /*<<< orphan*/  URL_PWDLEN ; 
 int URL_SCHEMELEN ; 
 int /*<<< orphan*/  URL_USERLEN ; 
 struct url* calloc (int,int) ; 
 char* fetch_pctdecode (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/  free (struct url*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 char* strpbrk (char const*,char*) ; 
 int strspn (char const*,char*) ; 
 char* strstr (char const*,char*) ; 
 void* tolower (unsigned char) ; 
 int /*<<< orphan*/  url_seterr (int /*<<< orphan*/ ) ; 

struct url *
fetchParseURL(const char *URL)
{
	char *doc;
	const char *p, *q;
	struct url *u;
	int i, n;

	/* allocate struct url */
	if ((u = calloc(1, sizeof(*u))) == NULL) {
		fetch_syserr();
		return (NULL);
	}
	u->netrcfd = -1;

	/* scheme name */
	if ((p = strstr(URL, ":/"))) {
                if (p - URL > URL_SCHEMELEN)
                        goto ouch;
                for (i = 0; URL + i < p; i++)
                        u->scheme[i] = tolower((unsigned char)URL[i]);
		URL = ++p;
		/*
		 * Only one slash: no host, leave slash as part of document
		 * Two slashes: host follows, strip slashes
		 */
		if (URL[1] == '/')
			URL = (p += 2);
	} else {
		p = URL;
	}
	if (!*URL || *URL == '/' || *URL == '.' ||
	    (u->scheme[0] == '\0' &&
		strchr(URL, '/') == NULL && strchr(URL, ':') == NULL))
		goto nohost;

	p = strpbrk(URL, "/@");
	if (p && *p == '@') {
		/* username */
		q = fetch_pctdecode(u->user, URL, URL_USERLEN);

		/* password */
		if (*q == ':')
			q = fetch_pctdecode(u->pwd, q + 1, URL_PWDLEN);

		p++;
	} else {
		p = URL;
	}

	/* hostname */
	if (*p == '[') {
		q = p + 1 + strspn(p + 1, ":0123456789ABCDEFabcdef");
		if (*q++ != ']')
			goto ouch;
	} else {
		/* valid characters in a DNS name */
		q = p + strspn(p, "-." "0123456789"
		    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "_"
		    "abcdefghijklmnopqrstuvwxyz");
	}
	if ((*q != '\0' && *q != '/' && *q != ':') || q - p > MAXHOSTNAMELEN)
		goto ouch;
	for (i = 0; p + i < q; i++)
		u->host[i] = tolower((unsigned char)p[i]);
	u->host[i] = '\0';
	p = q;

	/* port */
	if (*p == ':') {
		for (n = 0, q = ++p; *q && (*q != '/'); q++) {
			if (*q >= '0' && *q <= '9' && n < INT_MAX / 10) {
				n = n * 10 + (*q - '0');
			} else {
				/* invalid port */
				url_seterr(URL_BAD_PORT);
				goto ouch;
			}
		}
		if (n < 1 || n > IPPORT_MAX)
			goto ouch;
		u->port = n;
		p = q;
	}

nohost:
	/* document */
	if (!*p)
		p = "/";

	if (strcmp(u->scheme, SCHEME_HTTP) == 0 ||
	    strcmp(u->scheme, SCHEME_HTTPS) == 0) {
		const char hexnums[] = "0123456789abcdef";

		/* percent-escape whitespace. */
		if ((doc = malloc(strlen(p) * 3 + 1)) == NULL) {
			fetch_syserr();
			goto ouch;
		}
		u->doc = doc;
		while (*p != '\0') {
			if (!isspace((unsigned char)*p)) {
				*doc++ = *p++;
			} else {
				*doc++ = '%';
				*doc++ = hexnums[((unsigned int)*p) >> 4];
				*doc++ = hexnums[((unsigned int)*p) & 0xf];
				p++;
			}
		}
		*doc = '\0';
	} else if ((u->doc = strdup(p)) == NULL) {
		fetch_syserr();
		goto ouch;
	}

	DEBUGF("scheme:   \"%s\"\n"
	    "user:     \"%s\"\n"
	    "password: \"%s\"\n"
	    "host:     \"%s\"\n"
	    "port:     \"%d\"\n"
	    "document: \"%s\"\n",
	    u->scheme, u->user, u->pwd,
	    u->host, u->port, u->doc);

	return (u);

ouch:
	free(u);
	return (NULL);
}