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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  StringList ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int PMASK ; 
 int PROTOMAX ; 
 unsigned long ULONG_MAX ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 size_t getprotoindex (int /*<<< orphan*/ *,char*) ; 
 char* getstring (char const*,size_t,char**,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  sl_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * sl_find (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * sl_init () ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strsep (char**,char*) ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*,size_t,...) ; 

__attribute__((used)) static StringList ***
parseservices(const char *fname, StringList *sl)
{
	ssize_t len;
	size_t linecap, line, pindex;
	FILE *fp;
	StringList ***svc, *s;
	char *p, *ep;

	if ((fp = fopen(fname, "r")) == NULL)
		err(1, "Cannot open `%s'", fname);

	line = linecap = 0;
	if ((svc = calloc(PMASK + 1, sizeof(StringList **))) == NULL)
		err(1, "Cannot allocate %zu bytes", (size_t)(PMASK + 1));

	p = NULL;
	while ((len = getline(&p, &linecap, fp)) != -1) {
		char	*name, *port, *proto, *aliases, *cp, *alias;
		unsigned long pnum;

		line++;

		if (len == 0)
			continue;

		if (p[len - 1] == '\n')
			p[len - 1] = '\0';

		for (cp = p; *cp && isspace((unsigned char)*cp); cp++)
			continue;

		if (*cp == '\0' || *cp == '#')
			continue;

		if ((name = getstring(fname, line, &cp, "name")) == NULL)
			continue;

		if ((port = getstring(fname, line, &cp, "port")) == NULL)
			continue;

		if (cp) {
			for (aliases = cp; *cp && *cp != '#'; cp++)
				continue;

			if (*cp)
				*cp = '\0';
		} else
			aliases = NULL;

		proto = strchr(port, '/');
		if (proto == NULL || proto[1] == '\0') {
			warnx("%s, %zu: no protocol found", fname, line);
			continue;
		}
		*proto++ = '\0';

		errno = 0;
		pnum = strtoul(port, &ep, 0);
		if (*port == '\0' || *ep != '\0') {
			warnx("%s, %zu: invalid port `%s'", fname, line, port);
			continue;
		}
		if ((errno == ERANGE && pnum == ULONG_MAX) || pnum > PMASK) {
			warnx("%s, %zu: port too big `%s'", fname, line, port);
			continue;
		}

		if (svc[pnum] == NULL) {
			svc[pnum] = calloc(PROTOMAX, sizeof(StringList *));
			if (svc[pnum] == NULL)
				err(1, "Cannot allocate %zu bytes",
				    (size_t)PROTOMAX);
		}

		pindex = getprotoindex(sl, proto);
		if (svc[pnum][pindex] == NULL)
			s = svc[pnum][pindex] = sl_init();
		else
			s = svc[pnum][pindex];

		/* build list of aliases */
		if (sl_find(s, name) == NULL) {
			char *p2;

			if ((p2 = strdup(name)) == NULL)
				err(1, "Cannot copy string");
			(void)sl_add(s, p2);
		}

		if (aliases) {
			while ((alias = strsep(&aliases, " \t")) != NULL) {
				if (alias[0] == '\0')
					continue;
				if (sl_find(s, alias) == NULL) {
					char *p2;

					if ((p2 = strdup(alias)) == NULL)
						err(1, "Cannot copy string");
					(void)sl_add(s, p2);
				}
			}
		}
	}
	(void)fclose(fp);
	return svc;
}