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
typedef  enum mandoc_esc { ____Placeholder_mandoc_esc } mandoc_esc ;

/* Variables and functions */
 char const ASCII_HYPH ; 
 int ESCAPE_BREAK ; 
 int ESCAPE_DEVICE ; 
 int ESCAPE_ERROR ; 
#define  ESCAPE_FONT 129 
 int ESCAPE_HLINE ; 
 int ESCAPE_HORIZ ; 
 int ESCAPE_IGNORE ; 
 int ESCAPE_NOSPACE ; 
 int ESCAPE_NUMBERED ; 
 int ESCAPE_OVERSTRIKE ; 
 int ESCAPE_SKIPCHAR ; 
#define  ESCAPE_SPECIAL 128 
 int ESCAPE_UNDEF ; 
 int ESCAPE_UNICODE ; 
 int ESCAPE_UNSUPP ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int mandoc_font (char const*,int) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 scalar_t__ strspn (char const*,char*) ; 

enum mandoc_esc
mandoc_escape(const char **end, const char **start, int *sz)
{
	const char	*local_start;
	int		 local_sz, c, i;
	char		 term;
	enum mandoc_esc	 gly;

	/*
	 * When the caller doesn't provide return storage,
	 * use local storage.
	 */

	if (NULL == start)
		start = &local_start;
	if (NULL == sz)
		sz = &local_sz;

	/*
	 * Treat "\E" just like "\";
	 * it only makes a difference in copy mode.
	 */

	if (**end == 'E')
		++*end;

	/*
	 * Beyond the backslash, at least one input character
	 * is part of the escape sequence.  With one exception
	 * (see below), that character won't be returned.
	 */

	gly = ESCAPE_ERROR;
	*start = ++*end;
	*sz = 0;
	term = '\0';

	switch ((*start)[-1]) {
	/*
	 * First the glyphs.  There are several different forms of
	 * these, but each eventually returns a substring of the glyph
	 * name.
	 */
	case '(':
		gly = ESCAPE_SPECIAL;
		*sz = 2;
		break;
	case '[':
		if (**start == ' ') {
			++*end;
			return ESCAPE_ERROR;
		}
		gly = ESCAPE_SPECIAL;
		term = ']';
		break;
	case 'C':
		if ('\'' != **start)
			return ESCAPE_ERROR;
		*start = ++*end;
		gly = ESCAPE_SPECIAL;
		term = '\'';
		break;

	/*
	 * Escapes taking no arguments at all.
	 */
	case '!':
	case '?':
		return ESCAPE_UNSUPP;
	case '%':
	case '&':
	case ')':
	case ',':
	case '/':
	case '^':
	case 'a':
	case 'd':
	case 'r':
	case 't':
	case 'u':
	case '{':
	case '|':
	case '}':
		return ESCAPE_IGNORE;
	case 'c':
		return ESCAPE_NOSPACE;
	case 'p':
		return ESCAPE_BREAK;

	/*
	 * The \z escape is supposed to output the following
	 * character without advancing the cursor position.
	 * Since we are mostly dealing with terminal mode,
	 * let us just skip the next character.
	 */
	case 'z':
		return ESCAPE_SKIPCHAR;

	/*
	 * Handle all triggers matching \X(xy, \Xx, and \X[xxxx], where
	 * 'X' is the trigger.  These have opaque sub-strings.
	 */
	case 'F':
	case 'f':
	case 'g':
	case 'k':
	case 'M':
	case 'm':
	case 'n':
	case 'O':
	case 'V':
	case 'Y':
		gly = (*start)[-1] == 'f' ? ESCAPE_FONT : ESCAPE_IGNORE;
		switch (**start) {
		case '(':
			if ((*start)[-1] == 'O')
				gly = ESCAPE_ERROR;
			*start = ++*end;
			*sz = 2;
			break;
		case '[':
			if ((*start)[-1] == 'O')
				gly = (*start)[1] == '5' ?
				    ESCAPE_UNSUPP : ESCAPE_ERROR;
			*start = ++*end;
			term = ']';
			break;
		default:
			if ((*start)[-1] == 'O') {
				switch (**start) {
				case '0':
					gly = ESCAPE_UNSUPP;
					break;
				case '1':
				case '2':
				case '3':
				case '4':
					break;
				default:
					gly = ESCAPE_ERROR;
					break;
				}
			}
			*sz = 1;
			break;
		}
		break;
	case '*':
		if (strncmp(*start, "(.T", 3) != 0)
			abort();
		gly = ESCAPE_DEVICE;
		*start = ++*end;
		*sz = 2;
		break;

	/*
	 * These escapes are of the form \X'Y', where 'X' is the trigger
	 * and 'Y' is any string.  These have opaque sub-strings.
	 * The \B and \w escapes are handled in roff.c, roff_res().
	 */
	case 'A':
	case 'b':
	case 'D':
	case 'R':
	case 'X':
	case 'Z':
		gly = ESCAPE_IGNORE;
		/* FALLTHROUGH */
	case 'o':
		if (**start == '\0')
			return ESCAPE_ERROR;
		if (gly == ESCAPE_ERROR)
			gly = ESCAPE_OVERSTRIKE;
		term = **start;
		*start = ++*end;
		break;

	/*
	 * These escapes are of the form \X'N', where 'X' is the trigger
	 * and 'N' resolves to a numerical expression.
	 */
	case 'h':
	case 'H':
	case 'L':
	case 'l':
	case 'S':
	case 'v':
	case 'x':
		if (strchr(" %&()*+-./0123456789:<=>", **start)) {
			if ('\0' != **start)
				++*end;
			return ESCAPE_ERROR;
		}
		switch ((*start)[-1]) {
		case 'h':
			gly = ESCAPE_HORIZ;
			break;
		case 'l':
			gly = ESCAPE_HLINE;
			break;
		default:
			gly = ESCAPE_IGNORE;
			break;
		}
		term = **start;
		*start = ++*end;
		break;

	/*
	 * Special handling for the numbered character escape.
	 * XXX Do any other escapes need similar handling?
	 */
	case 'N':
		if ('\0' == **start)
			return ESCAPE_ERROR;
		(*end)++;
		if (isdigit((unsigned char)**start)) {
			*sz = 1;
			return ESCAPE_IGNORE;
		}
		(*start)++;
		while (isdigit((unsigned char)**end))
			(*end)++;
		*sz = *end - *start;
		if ('\0' != **end)
			(*end)++;
		return ESCAPE_NUMBERED;

	/*
	 * Sizes get a special category of their own.
	 */
	case 's':
		gly = ESCAPE_IGNORE;

		/* See +/- counts as a sign. */
		if ('+' == **end || '-' == **end || ASCII_HYPH == **end)
			*start = ++*end;

		switch (**end) {
		case '(':
			*start = ++*end;
			*sz = 2;
			break;
		case '[':
			*start = ++*end;
			term = ']';
			break;
		case '\'':
			*start = ++*end;
			term = '\'';
			break;
		case '3':
		case '2':
		case '1':
			*sz = (*end)[-1] == 's' &&
			    isdigit((unsigned char)(*end)[1]) ? 2 : 1;
			break;
		default:
			*sz = 1;
			break;
		}

		break;

	/*
	 * Several special characters can be encoded as
	 * one-byte escape sequences without using \[].
	 */
	case ' ':
	case '\'':
	case '-':
	case '.':
	case '0':
	case ':':
	case '_':
	case '`':
	case 'e':
	case '~':
		gly = ESCAPE_SPECIAL;
		/* FALLTHROUGH */
	default:
		if (gly == ESCAPE_ERROR)
			gly = ESCAPE_UNDEF;
		*start = --*end;
		*sz = 1;
		break;
	}

	/*
	 * Read up to the terminating character,
	 * paying attention to nested escapes.
	 */

	if ('\0' != term) {
		while (**end != term) {
			switch (**end) {
			case '\0':
				return ESCAPE_ERROR;
			case '\\':
				(*end)++;
				if (ESCAPE_ERROR ==
				    mandoc_escape(end, NULL, NULL))
					return ESCAPE_ERROR;
				break;
			default:
				(*end)++;
				break;
			}
		}
		*sz = (*end)++ - *start;

		/*
		 * The file chars.c only provides one common list
		 * of character names, but \[-] == \- is the only
		 * one of the characters with one-byte names that
		 * allows enclosing the name in brackets.
		 */
		if (gly == ESCAPE_SPECIAL && *sz == 1 && **start != '-')
			return ESCAPE_ERROR;
	} else {
		assert(*sz > 0);
		if ((size_t)*sz > strlen(*start))
			return ESCAPE_ERROR;
		*end += *sz;
	}

	/* Run post-processors. */

	switch (gly) {
	case ESCAPE_FONT:
		gly = mandoc_font(*start, *sz);
		break;
	case ESCAPE_SPECIAL:
		if (**start == 'c') {
			if (*sz < 6 || *sz > 7 ||
			    strncmp(*start, "char", 4) != 0 ||
			    (int)strspn(*start + 4, "0123456789") + 4 < *sz)
				break;
			c = 0;
			for (i = 4; i < *sz; i++)
				c = 10 * c + ((*start)[i] - '0');
			if (c < 0x21 || (c > 0x7e && c < 0xa0) || c > 0xff)
				break;
			*start += 4;
			*sz -= 4;
			gly = ESCAPE_NUMBERED;
			break;
		}

		/*
		 * Unicode escapes are defined in groff as \[u0000]
		 * to \[u10FFFF], where the contained value must be
		 * a valid Unicode codepoint.  Here, however, only
		 * check the length and range.
		 */
		if (**start != 'u' || *sz < 5 || *sz > 7)
			break;
		if (*sz == 7 && ((*start)[1] != '1' || (*start)[2] != '0'))
			break;
		if (*sz == 6 && (*start)[1] == '0')
			break;
		if (*sz == 5 && (*start)[1] == 'D' &&
		    strchr("89ABCDEF", (*start)[2]) != NULL)
			break;
		if ((int)strspn(*start + 1, "0123456789ABCDEFabcdef")
		    + 1 == *sz)
			gly = ESCAPE_UNICODE;
		break;
	default:
		break;
	}

	return gly;
}