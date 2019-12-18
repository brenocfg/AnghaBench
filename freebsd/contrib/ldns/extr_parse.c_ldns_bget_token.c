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
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int EOF ; 
 char* LDNS_PARSE_NORMAL ; 
 int ldns_bgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_bskipcs (int /*<<< orphan*/ *,char const*) ; 

ssize_t
ldns_bget_token(ldns_buffer *b, char *token, const char *delim, size_t limit)
{
	int c, lc;
	int p; /* 0 -> no parenthese seen, >0 nr of ( seen */
	int com, quoted;
	char *t;
	size_t i;
	const char *d;
	const char *del;

	/* standard delimiters */
	if (!delim) {
		/* from isspace(3) */
		del = LDNS_PARSE_NORMAL;
	} else {
		del = delim;
	}

	p = 0;
	i = 0;
	com = 0;
	quoted = 0;
	t = token;
	lc = 0;
	if (del[0] == '"') {
		quoted = 1;
	}

	while ((c = ldns_bgetc(b)) != EOF) {
		if (c == '\r') /* carriage return */
			c = ' ';
		if (c == '(' && lc != '\\' && !quoted) {
			/* this only counts for non-comments */
			if (com == 0) {
				p++;
			}
			lc = c;
			continue;
		}

		if (c == ')' && lc != '\\' && !quoted) {
			/* this only counts for non-comments */
			if (com == 0) {
				p--;
			}
			lc = c;
			continue;
		}

		if (p < 0) {
			/* more ) then ( */
			*t = '\0';
			return 0;
		}

		/* do something with comments ; */
		if (c == ';' && quoted == 0) {
			if (lc != '\\') {
				com = 1;
			}
		}
		if (c == '"' && com == 0 && lc != '\\') {
			quoted = 1 - quoted;
		}

		if (c == '\n' && com != 0) {
			/* comments */
			com = 0;
			*t = ' ';
			lc = c;
			continue;
		}

		if (com == 1) {
			*t = ' ';
			lc = c;
			continue;
		}

		if (c == '\n' && p != 0) {
			/* in parentheses */
			*t++ = ' ';
			lc = c;
			continue;
		}

		/* check if we hit the delim */
		for (d = del; *d; d++) {
                        if (c == *d && lc != '\\' && p == 0) {
				goto tokenread;
                        }
		}

		i++;
		if (limit > 0 && (i >= limit || (size_t)(t-token) >= limit)) {
			*t = '\0';
			return -1;
		}
		*t++ = c;

		if (c == '\\' && lc == '\\') {
			lc = 0;
		} else {
			lc = c;
		}
	}
	*t = '\0';
	if (i == 0) {
		/* nothing read */
		return -1;
	}
	if (p != 0) {
		return -1;
	}
	return (ssize_t)i;

tokenread:
	if(*del == '"') /* do not skip over quotes, they are significant */
		ldns_bskipcs(b, del+1);
	else	ldns_bskipcs(b, del);
	*t = '\0';

	if (p != 0) {
		return -1;
	}
	return (ssize_t)i;
}