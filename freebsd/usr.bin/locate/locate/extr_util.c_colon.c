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

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 void* malloc (int) ; 
 char** realloc (char**,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

char **
colon(char **dbv, char *path, char *dot)
{
	int vlen, slen;
	char *c, *ch, *p;
	char **pv;

	if (dbv == NULL) {
		if ((dbv = malloc(sizeof(char *))) == NULL)
			err(1, "malloc");
		*dbv = NULL;
	}

	/* empty string */
	if (*path == '\0') {
		warnx("empty database name, ignored");
		return(dbv);
	}

	/* length of string vector */
	for(vlen = 0, pv = dbv; *pv != NULL; pv++, vlen++);

	for (ch = c = path; ; ch++) {
		if (*ch == ':' ||
		    (!*ch && !(*(ch - 1) == ':' && ch == 1+ path))) {
			/* single colon -> dot */
			if (ch == c)
				p = dot;
			else {
				/* a string */
				slen = ch - c;
				if ((p = malloc(sizeof(char) * (slen + 1))) 
				    == NULL)
					err(1, "malloc");
				bcopy(c, p, slen);
				*(p + slen) = '\0';
			}
			/* increase dbv with element p */
			if ((dbv = realloc(dbv, sizeof(char *) * (vlen + 2)))
			    == NULL)
				err(1, "realloc");
			*(dbv + vlen) = p;
			*(dbv + ++vlen) = NULL;
			c = ch + 1;
		}
		if (*ch == '\0')
			break;
	}
	return (dbv);
}