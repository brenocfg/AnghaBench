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
struct roff_man {int flags; int /*<<< orphan*/  roff; } ;
typedef  enum margserr { ____Placeholder_margserr } margserr ;
typedef  enum argsflag { ____Placeholder_argsflag } argsflag ;

/* Variables and functions */
 int ARGSFL_DELIM ; 
 int ARGSFL_TABSEP ; 
 int ARGS_ALLOC ; 
 int ARGS_EOLN ; 
 int ARGS_PHRASE ; 
 int ARGS_PUNCT ; 
 int ARGS_WORD ; 
 int /*<<< orphan*/  MANDOCERR_ARG_QUOTE ; 
 int /*<<< orphan*/  MANDOCERR_SPACE_EOL ; 
 int MDOC_PHRASE ; 
 int MDOC_PHRASELIT ; 
 int MDOC_PHRASEQF ; 
 int MDOC_PHRASEQL ; 
 int MDOC_PHRASEQN ; 
 scalar_t__ args_checkpunct (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 char* roff_getarg (int /*<<< orphan*/ ,char**,int,int*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static enum margserr
args(struct roff_man *mdoc, int line, int *pos,
		char *buf, enum argsflag fl, char **v)
{
	char		*p;
	char		*v_local;
	int		 pairs;

	if (buf[*pos] == '\0') {
		if (mdoc->flags & MDOC_PHRASELIT &&
		    ! (mdoc->flags & MDOC_PHRASE)) {
			mandoc_msg(MANDOCERR_ARG_QUOTE, line, *pos, NULL);
			mdoc->flags &= ~MDOC_PHRASELIT;
		}
		mdoc->flags &= ~MDOC_PHRASEQL;
		return ARGS_EOLN;
	}

	if (v == NULL)
		v = &v_local;
	*v = buf + *pos;

	if (fl == ARGSFL_DELIM && args_checkpunct(buf, *pos))
		return ARGS_PUNCT;

	/*
	 * Tabs in `It' lines in `Bl -column' can't be escaped.
	 * Phrases are reparsed for `Ta' and other macros later.
	 */

	if (fl == ARGSFL_TABSEP) {
		if ((p = strchr(*v, '\t')) != NULL) {

			/*
			 * Words right before and right after
			 * tab characters are not parsed,
			 * unless there is a blank in between.
			 */

			if (p > buf && p[-1] != ' ')
				mdoc->flags |= MDOC_PHRASEQL;
			if (p[1] != ' ')
				mdoc->flags |= MDOC_PHRASEQN;

			/*
			 * One or more blanks after a tab cause
			 * one leading blank in the next column.
			 * So skip all but one of them.
			 */

			*pos += (int)(p - *v) + 1;
			while (buf[*pos] == ' ' && buf[*pos + 1] == ' ')
				(*pos)++;

			/*
			 * A tab at the end of an input line
			 * switches to the next column.
			 */

			if (buf[*pos] == '\0' || buf[*pos + 1] == '\0')
				mdoc->flags |= MDOC_PHRASEQN;
		} else {
			p = strchr(*v, '\0');
			if (p[-1] == ' ')
				mandoc_msg(MANDOCERR_SPACE_EOL,
				    line, *pos, NULL);
			*pos += (int)(p - *v);
		}

		/* Skip any trailing blank characters. */
		while (p > *v && p[-1] == ' ' &&
		    (p - 1 == *v || p[-2] != '\\'))
			p--;
		*p = '\0';

		return ARGS_PHRASE;
	}

	/*
	 * Process a quoted literal.  A quote begins with a double-quote
	 * and ends with a double-quote NOT preceded by a double-quote.
	 * NUL-terminate the literal in place.
	 * Collapse pairs of quotes inside quoted literals.
	 * Whitespace is NOT involved in literal termination.
	 */

	if (mdoc->flags & MDOC_PHRASELIT ||
	    (mdoc->flags & MDOC_PHRASE && buf[*pos] == '\"')) {
		if ((mdoc->flags & MDOC_PHRASELIT) == 0) {
			*v = &buf[++(*pos)];
			mdoc->flags |= MDOC_PHRASELIT;
		}
		pairs = 0;
		for ( ; buf[*pos]; (*pos)++) {
			/* Move following text left after quoted quotes. */
			if (pairs)
				buf[*pos - pairs] = buf[*pos];
			if ('\"' != buf[*pos])
				continue;
			/* Unquoted quotes end quoted args. */
			if ('\"' != buf[*pos + 1])
				break;
			/* Quoted quotes collapse. */
			pairs++;
			(*pos)++;
		}
		if (pairs)
			buf[*pos - pairs] = '\0';

		if (buf[*pos] == '\0') {
			if ( ! (mdoc->flags & MDOC_PHRASE))
				mandoc_msg(MANDOCERR_ARG_QUOTE,
				    line, *pos, NULL);
			return ARGS_WORD;
		}

		mdoc->flags &= ~MDOC_PHRASELIT;
		buf[(*pos)++] = '\0';

		if ('\0' == buf[*pos])
			return ARGS_WORD;

		while (' ' == buf[*pos])
			(*pos)++;

		if ('\0' == buf[*pos])
			mandoc_msg(MANDOCERR_SPACE_EOL, line, *pos, NULL);

		return ARGS_WORD;
	}

	p = &buf[*pos];
	*v = roff_getarg(mdoc->roff, &p, line, pos);
	if (v == &v_local)
		free(*v);

	/*
	 * After parsing the last word in this phrase,
	 * tell lookup() whether or not to interpret it.
	 */

	if (*p == '\0' && mdoc->flags & MDOC_PHRASEQL) {
		mdoc->flags &= ~MDOC_PHRASEQL;
		mdoc->flags |= MDOC_PHRASEQF;
	}
	return ARGS_ALLOC;
}