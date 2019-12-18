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
struct servent {int /*<<< orphan*/  s_port; } ;
struct protoent {int /*<<< orphan*/ * p_name; } ;

/* Variables and functions */
 int IPPROTO_ETHERTYPE ; 
 int /*<<< orphan*/  ether_types ; 
 int /*<<< orphan*/  free (char*) ; 
 struct protoent* getprotobynumber (int) ; 
 struct servent* getservbyname (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isdigit (char) ; 
 int match_token (int /*<<< orphan*/ ,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 char* safe_calloc (int,int) ; 
 int /*<<< orphan*/  setservent (int) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int
strtoport(char *s, char **end, int base, int proto)
{
	char *p, *buf;
	char *s1;
	int i;

	*end = s;		/* default - not found */
	if (*s == '\0')
		return 0;	/* not found */

	if (isdigit(*s))
		return strtol(s, end, base);

	/*
	 * find separator. '\\' escapes the next char.
	 */
	for (s1 = s; *s1 && (isalnum(*s1) || *s1 == '\\' ||
	    *s1 == '_' || *s1 == '.') ; s1++)
		if (*s1 == '\\' && s1[1] != '\0')
			s1++;

	buf = safe_calloc(s1 - s + 1, 1);

	/*
	 * copy into a buffer skipping backslashes
	 */
	for (p = s, i = 0; p != s1 ; p++)
		if (*p != '\\')
			buf[i++] = *p;
	buf[i++] = '\0';

	if (proto == IPPROTO_ETHERTYPE) {
		i = match_token(ether_types, buf);
		free(buf);
		if (i != -1) {	/* found */
			*end = s1;
			return i;
		}
	} else {
		struct protoent *pe = NULL;
		struct servent *se;

		if (proto != 0)
			pe = getprotobynumber(proto);
		setservent(1);
		se = getservbyname(buf, pe ? pe->p_name : NULL);
		free(buf);
		if (se != NULL) {
			*end = s1;
			return ntohs(se->s_port);
		}
	}
	return 0;	/* not found */
}