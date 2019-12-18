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
 size_t PARSE_BUFSIZE ; 
 int /*<<< orphan*/  PARSE_FAIL (int) ; 
 int /*<<< orphan*/ ** args ; 
 char* backslash (char const*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ **,char**,int) ; 
 int /*<<< orphan*/  clean () ; 
 int /*<<< orphan*/  free (char*) ; 
 int insert (int*,char*) ; 
 char isdelim (char) ; 
 int /*<<< orphan*/  isdquote (char) ; 
 int /*<<< orphan*/  isquote (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 scalar_t__ malloc (int) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* variable_lookup (char*) ; 

int
parse(int *argc, char ***argv, const char *str)
{
	int ac;
	char *val, *p, *q, *copy = NULL;
	size_t i = 0;
	char token, tmp, quote, dquote, *buf;
	enum { STR, VAR, WHITE } state;

	ac = *argc = 0;
	dquote = quote = 0;
	if (!str || (p = copy = backslash(str)) == NULL)
		return 1;

	/* Initialize vector and state */
	clean();
	state = STR;
	buf = (char *)malloc(PARSE_BUFSIZE);
	token = 0;

	/* And awaaaaaaaaay we go! */
	while (*p) {
		switch (state) {
		case STR:
			if ((*p == '\\') && p[1]) {
				p++;
				PARSE_FAIL(i == (PARSE_BUFSIZE - 1));
				buf[i++] = *p++;
			} else if (isquote(*p)) {
				quote = quote ? 0 : *p;
				if (dquote) { /* keep quote */
					PARSE_FAIL(i == (PARSE_BUFSIZE - 1));
					buf[i++] = *p++;
				} else
					++p;
			} else if (isdquote(*p)) {
				dquote = dquote ? 0 : *p;
				if (quote) { /* keep dquote */
					PARSE_FAIL(i == (PARSE_BUFSIZE - 1));
					buf[i++] = *p++;
				} else
					++p;
			} else if (isspace(*p) && !quote && !dquote) {
				state = WHITE;
				if (i) {
					buf[i] = '\0';
					PARSE_FAIL(insert(&ac, buf));
					i = 0;
				}
				++p;
			} else if (*p == '$' && !quote) {
				token = isdelim(*(p + 1));
				if (token)
					p += 2;
				else
					++p;
				state = VAR;
			} else {
				PARSE_FAIL(i == (PARSE_BUFSIZE - 1));
				buf[i++] = *p++;
			}
			break;

		case WHITE:
			if (isspace(*p))
				++p;
			else
				state = STR;
			break;

		case VAR:
			if (token) {
				PARSE_FAIL((q = strchr(p, token)) == NULL);
			} else {
				q = p;
				while (*q && !isspace(*q))
					++q;
			}
			tmp = *q;
			*q = '\0';
			if ((val = variable_lookup(p)) != NULL) {
				size_t len = strlen(val);

				strncpy(buf + i, val, PARSE_BUFSIZE - (i + 1));
				i += min(len, PARSE_BUFSIZE - 1);
			}
			*q = tmp;	/* restore value */
			p = q + (token ? 1 : 0);
			state = STR;
			break;
		}
	}
	/* missing terminating ' or " */
	PARSE_FAIL(quote || dquote);
	/* If at end of token, add it */
	if (i && state == STR) {
		buf[i] = '\0';
		PARSE_FAIL(insert(&ac, buf));
	}
	args[ac] = NULL;
	*argc = ac;
	*argv = (char **)malloc((sizeof(char *) * ac + 1));
	bcopy(args, *argv, sizeof(char *) * ac + 1);
	free(buf);
	free(copy);
	return 0;
}