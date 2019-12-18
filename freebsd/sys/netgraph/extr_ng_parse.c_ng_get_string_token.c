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
 int /*<<< orphan*/  M_NETGRAPH_PARSE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tolower (char) ; 

char *
ng_get_string_token(const char *s, int *startp, int *lenp, int *slenp)
{
	char *cbuf, *p;
	int start, off;
	int slen;

	while (isspace(s[*startp]))
		(*startp)++;
	start = *startp;
	if (s[*startp] != '"')
		return (NULL);
	cbuf = malloc(strlen(s + start), M_NETGRAPH_PARSE, M_NOWAIT);
	if (cbuf == NULL)
		return (NULL);
	strcpy(cbuf, s + start + 1);
	for (slen = 0, off = 1, p = cbuf; *p != '\0'; slen++, off++, p++) {
		if (*p == '"') {
			*p = '\0';
			*lenp = off + 1;
			if (slenp != NULL)
				*slenp = slen;
			return (cbuf);
		} else if (p[0] == '\\' && p[1] != '\0') {
			int x, k;
			char *v;

			strcpy(p, p + 1);
			v = p;
			switch (*p) {
			case 't':
				*v = '\t';
				off++;
				continue;
			case 'n':
				*v = '\n';
				off++;
				continue;
			case 'r':
				*v = '\r';
				off++;
				continue;
			case 'v':
				*v =  '\v';
				off++;
				continue;
			case 'f':
				*v =  '\f';
				off++;
				continue;
			case '"':
				*v =  '"';
				off++;
				continue;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
				for (x = k = 0;
				    k < 3 && *v >= '0' && *v <= '7'; v++) {
					x = (x << 3) + (*v - '0');
					off++;
				}
				*--v = (char)x;
				break;
			case 'x':
				for (v++, x = k = 0;
				    k < 2 && isxdigit(*v); v++) {
					x = (x << 4) + (isdigit(*v) ?
					      (*v - '0') :
					      (tolower(*v) - 'a' + 10));
					off++;
				}
				*--v = (char)x;
				break;
			default:
				continue;
			}
			strcpy(p, v);
		}
	}
	free(cbuf, M_NETGRAPH_PARSE);
	return (NULL);		/* no closing quote */
}