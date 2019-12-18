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
 int /*<<< orphan*/  err (int,char*) ; 
 char* malloc (scalar_t__) ; 
 char* realloc (char*,scalar_t__) ; 
 char* skip_comment (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 

char *
skin(char *name)
{
	char *nbuf, *bufend, *cp, *cp2;
	int c, gotlt, lastsp;

	if (name == NULL)
		return (NULL);
	if (strchr(name, '(') == NULL && strchr(name, '<') == NULL
	    && strchr(name, ' ') == NULL)
		return (name);

	/* We assume that length(input) <= length(output) */
	if ((nbuf = malloc(strlen(name) + 1)) == NULL)
		err(1, "Out of memory");
	gotlt = 0;
	lastsp = 0;
	bufend = nbuf;
	for (cp = name, cp2 = bufend; (c = *cp++) != '\0'; ) {
		switch (c) {
		case '(':
			cp = skip_comment(cp);
			lastsp = 0;
			break;

		case '"':
			/*
			 * Start of a "quoted-string".
			 * Copy it in its entirety.
			 */
			while ((c = *cp) != '\0') {
				cp++;
				if (c == '"')
					break;
				if (c != '\\')
					*cp2++ = c;
				else if ((c = *cp) != '\0') {
					*cp2++ = c;
					cp++;
				}
			}
			lastsp = 0;
			break;

		case ' ':
			if (cp[0] == 'a' && cp[1] == 't' && cp[2] == ' ')
				cp += 3, *cp2++ = '@';
			else
			if (cp[0] == '@' && cp[1] == ' ')
				cp += 2, *cp2++ = '@';
			else
				lastsp = 1;
			break;

		case '<':
			cp2 = bufend;
			gotlt++;
			lastsp = 0;
			break;

		case '>':
			if (gotlt) {
				gotlt = 0;
				while ((c = *cp) != '\0' && c != ',') {
					cp++;
					if (c == '(')
						cp = skip_comment(cp);
					else if (c == '"')
						while ((c = *cp) != '\0') {
							cp++;
							if (c == '"')
								break;
							if (c == '\\' && *cp != '\0')
								cp++;
						}
				}
				lastsp = 0;
				break;
			}
			/* FALLTHROUGH */

		default:
			if (lastsp) {
				lastsp = 0;
				*cp2++ = ' ';
			}
			*cp2++ = c;
			if (c == ',' && !gotlt &&
			    (*cp == ' ' || *cp == '"' || *cp == '<')) {
				*cp2++ = ' ';
				while (*cp == ' ')
					cp++;
				lastsp = 0;
				bufend = cp2;
			}
		}
	}
	*cp2 = '\0';

	if ((cp = realloc(nbuf, strlen(nbuf) + 1)) != NULL)
		nbuf = cp;
	return (nbuf);
}