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
 int env_verbosity ; 
 int /*<<< orphan*/  errx (int,char*,char const,...) ; 
 char* expand_vars (int,char**,char**,char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ isspacech (char const) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

void
split_spaces(const char *str, int *origind, int *origc, char ***origv)
{
	static const char *nullarg = "";
	const char *bq_src, *copystr, *src;
	char *dest, **newargv, *newstr, **nextarg, **oldarg;
	int addcount, bq_destlen, copychar, found_sep, in_arg, in_dq, in_sq;

	/*
	 * Ignore leading space on the string, and then malloc enough room
	 * to build a copy of it.  The copy might end up shorter than the
	 * original, due to quoted strings and '\'-processing.
	 */
	while (isspacech(*str))
		str++;
	if (*str == '\0')
		return;
	newstr = malloc(strlen(str) + 1);

	/*
	 * Allocate plenty of space for the new array of arg-pointers,
	 * and start that array off with the first element of the old
	 * array.
	 */
	newargv = malloc((*origc + (strlen(str) / 2) + 2) * sizeof(char *));
	nextarg = newargv;
	*nextarg++ = **origv;

	/* Come up with the new args by splitting up the given string. */
	addcount = 0;
	bq_destlen = in_arg = in_dq = in_sq = 0;
	bq_src = NULL;
	for (src = str, dest = newstr; *src != '\0'; src++) {
		/*
		 * This switch will look at a character in *src, and decide
		 * what should be copied to *dest.  It only decides what
		 * character(s) to copy, it should not modify *dest.  In some
		 * cases, it will look at multiple characters from *src.
		 */
		copychar = found_sep = 0;
		copystr = NULL;
		switch (*src) {
		case '"':
			if (in_sq)
				copychar = *src;
			else if (in_dq)
				in_dq = 0;
			else {
				/*
				 * Referencing nullarg ensures that a new
				 * argument is created, even if this quoted
				 * string ends up with zero characters.
				 */
				copystr = nullarg;
				in_dq = 1;
				bq_destlen = dest - *(nextarg - 1);
				bq_src = src;
			}
			break;
		case '$':
			if (in_sq)
				copychar = *src;
			else {
				copystr = expand_vars(in_arg, (nextarg - 1),
				    &dest, &src);
			}
			break;
		case '\'':
			if (in_dq)
				copychar = *src;
			else if (in_sq)
				in_sq = 0;
			else {
				/*
				 * Referencing nullarg ensures that a new
				 * argument is created, even if this quoted
				 * string ends up with zero characters.
				 */
				copystr = nullarg;
				in_sq = 1;
				bq_destlen = dest - *(nextarg - 1);
				bq_src = src;
			}
			break;
		case '\\':
			if (in_sq) {
				/*
				 * Inside single-quoted strings, only the
				 * "\'" and "\\" are recognized as special
				 * strings.
				 */
				copychar = *(src + 1);
				if (copychar == '\'' || copychar == '\\')
					src++;
				else
					copychar = *src;
				break;
			}
			src++;
			switch (*src) {
			case '"':
			case '#':
			case '$':
			case '\'':
			case '\\':
				copychar = *src;
				break;
			case '_':
				/*
				 * Alternate way to get a blank, which allows
				 * that blank be used to separate arguments
				 * when it is not inside a quoted string.
				 */
				if (in_dq)
					copychar = ' ';
				else {
					found_sep = 1;
					src++;
				}
				break;
			case 'c':
				/*
				 * Ignore remaining characters in the -S string.
				 * This would not make sense if found in the
				 * middle of a quoted string.
				 */
				if (in_dq)
					errx(1, "Sequence '\\%c' is not allowed"
					    " in quoted strings", *src);
				goto str_done;
			case 'f':
				copychar = '\f';
				break;
			case 'n':
				copychar = '\n';
				break;
			case 'r':
				copychar = '\r';
				break;
			case 't':
				copychar = '\t';
				break;
			case 'v':
				copychar = '\v';
				break;
			default:
				if (isspacech(*src))
					copychar = *src;
				else
					errx(1, "Invalid sequence '\\%c' in -S",
					    *src);
			}
			break;
		default:
			if ((in_dq || in_sq) && in_arg)
				copychar = *src;
			else if (isspacech(*src))
				found_sep = 1;
			else {
				/*
				 * If the first character of a new argument
				 * is `#', then ignore the remaining chars.
				 */
				if (!in_arg && *src == '#')
					goto str_done;
				copychar = *src;
			}
		}
		/*
		 * Now that the switch has determined what (if anything)
		 * needs to be copied, copy whatever that is to *dest.
		 */
		if (copychar || copystr != NULL) {
			if (!in_arg) {
				/* This is the first byte of a new argument */
				*nextarg++ = dest;
				addcount++;
				in_arg = 1;
			}
			if (copychar)
				*dest++ = (char)copychar;
			else if (copystr != NULL)
				while (*copystr != '\0')
					*dest++ = *copystr++;
		} else if (found_sep) {
			*dest++ = '\0';
			while (isspacech(*src))
				src++;
			--src;
			in_arg = 0;
		}
	}
str_done:
	*dest = '\0';
	*nextarg = NULL;
	if (in_dq || in_sq) {
		errx(1, "No terminating quote for string: %.*s%s",
		    bq_destlen, *(nextarg - 1), bq_src);
	}
	if (env_verbosity > 1) {
		fprintf(stderr, "#env  split -S:\t'%s'\n", str);
		oldarg = newargv + 1;
		fprintf(stderr, "#env      into:\t'%s'\n", *oldarg);
		for (oldarg++; *oldarg; oldarg++)
			fprintf(stderr, "#env          &\t'%s'\n", *oldarg);
	}

	/* Copy the unprocessed arg-pointers from the original array */
	for (oldarg = *origv + *origind; *oldarg; oldarg++)
		*nextarg++ = *oldarg;
	*nextarg = NULL;

	/* Update optind/argc/argv in the calling routine */
	*origc += addcount - *origind + 1;
	*origv = newargv;
	*origind = 1;
}