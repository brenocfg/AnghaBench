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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int MAX_PROP ; 
 int /*<<< orphan*/  SEP ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strsep (char**,int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

char *
match_list(const char *client, const char *server, u_int *next)
{
	char *sproposals[MAX_PROP];
	char *c, *s, *p, *ret, *cp, *sp;
	int i, j, nproposals;

	c = cp = xstrdup(client);
	s = sp = xstrdup(server);

	for ((p = strsep(&sp, SEP)), i=0; p && *p != '\0';
	    (p = strsep(&sp, SEP)), i++) {
		if (i < MAX_PROP)
			sproposals[i] = p;
		else
			break;
	}
	nproposals = i;

	for ((p = strsep(&cp, SEP)), i=0; p && *p != '\0';
	    (p = strsep(&cp, SEP)), i++) {
		for (j = 0; j < nproposals; j++) {
			if (strcmp(p, sproposals[j]) == 0) {
				ret = xstrdup(p);
				if (next != NULL)
					*next = (cp == NULL) ?
					    strlen(c) : (u_int)(cp - c);
				free(c);
				free(s);
				return ret;
			}
		}
	}
	if (next != NULL)
		*next = strlen(c);
	free(c);
	free(s);
	return NULL;
}