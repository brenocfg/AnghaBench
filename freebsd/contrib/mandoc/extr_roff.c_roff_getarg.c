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
struct roff {int dummy; } ;
struct buf {char* buf; int /*<<< orphan*/ * next; scalar_t__ sz; } ;

/* Variables and functions */
 char ASCII_ESC ; 
 int /*<<< orphan*/  MANDOCERR_ARG_QUOTE ; 
 int /*<<< orphan*/  MANDOCERR_SPACE_EOL ; 
 int ROFF_IGN ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 void* mandoc_strdup (char*) ; 
 int roff_expand (struct roff*,struct buf*,int,int /*<<< orphan*/ ,char) ; 
 scalar_t__ strlen (char*) ; 

char *
roff_getarg(struct roff *r, char **cpp, int ln, int *pos)
{
	struct buf	 buf;
	char		*cp, *start;
	int		 newesc, pairs, quoted, white;

	/* Quoting can only start with a new word. */
	start = *cpp;
	quoted = 0;
	if ('"' == *start) {
		quoted = 1;
		start++;
	}

	newesc = pairs = white = 0;
	for (cp = start; '\0' != *cp; cp++) {

		/*
		 * Move the following text left
		 * after quoted quotes and after "\\" and "\t".
		 */
		if (pairs)
			cp[-pairs] = cp[0];

		if ('\\' == cp[0]) {
			/*
			 * In copy mode, translate double to single
			 * backslashes and backslash-t to literal tabs.
			 */
			switch (cp[1]) {
			case 'a':
			case 't':
				cp[-pairs] = '\t';
				pairs++;
				cp++;
				break;
			case '\\':
				newesc = 1;
				cp[-pairs] = ASCII_ESC;
				pairs++;
				cp++;
				break;
			case ' ':
				/* Skip escaped blanks. */
				if (0 == quoted)
					cp++;
				break;
			default:
				break;
			}
		} else if (0 == quoted) {
			if (' ' == cp[0]) {
				/* Unescaped blanks end unquoted args. */
				white = 1;
				break;
			}
		} else if ('"' == cp[0]) {
			if ('"' == cp[1]) {
				/* Quoted quotes collapse. */
				pairs++;
				cp++;
			} else {
				/* Unquoted quotes end quoted args. */
				quoted = 2;
				break;
			}
		}
	}

	/* Quoted argument without a closing quote. */
	if (1 == quoted)
		mandoc_msg(MANDOCERR_ARG_QUOTE, ln, *pos, NULL);

	/* NUL-terminate this argument and move to the next one. */
	if (pairs)
		cp[-pairs] = '\0';
	if ('\0' != *cp) {
		*cp++ = '\0';
		while (' ' == *cp)
			cp++;
	}
	*pos += (int)(cp - start) + (quoted ? 1 : 0);
	*cpp = cp;

	if ('\0' == *cp && (white || ' ' == cp[-1]))
		mandoc_msg(MANDOCERR_SPACE_EOL, ln, *pos, NULL);

	start = mandoc_strdup(start);
	if (newesc == 0)
		return start;

	buf.buf = start;
	buf.sz = strlen(start) + 1;
	buf.next = NULL;
	if (roff_expand(r, &buf, ln, 0, ASCII_ESC) & ROFF_IGN) {
		free(buf.buf);
		buf.buf = mandoc_strdup("");
	}
	return buf.buf;
}