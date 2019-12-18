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
 int /*<<< orphan*/  ISODIGIT (unsigned char) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  isxdigit (unsigned char) ; 
 int /*<<< orphan*/  toupper (unsigned char) ; 

__attribute__((used)) static char *
unescape(char *orig)
{
	char c, *cp, *new = orig;
	int i;

	for (cp = orig; (*orig = *cp); cp++, orig++) {
		if (*cp != '\\')
			continue;

		switch (*++cp) {
		case 'a':	/* alert (bell) */
			*orig = '\a';
			continue;
		case 'b':	/* backspace */
			*orig = '\b';
			continue;
		case 'e':	/* escape */
			*orig = '\e';
			continue;
		case 'f':	/* formfeed */
			*orig = '\f';
			continue;
		case 'n':	/* newline */
			*orig = '\n';
			continue;
		case 'r':	/* carriage return */
			*orig = '\r';
			continue;
		case 't':	/* horizontal tab */
			*orig = '\t';
			continue;
		case 'v':	/* vertical tab */
			*orig = '\v';
			continue;
		case '\\':	/* backslash */
			*orig = '\\';
			continue;
		case '\'':	/* single quote */
			*orig = '\'';
			continue;
		case '\"':	/* double quote */
			*orig = '"';
			continue;
		case '0':
		case '1':
		case '2':
		case '3':	/* octal */
		case '4':
		case '5':
		case '6':
		case '7':	/* number */
			for (i = 0, c = 0;
			     ISODIGIT((unsigned char)*cp) && i < 3;
			     i++, cp++) {
				c <<= 3;
				c |= (*cp - '0');
			}
			*orig = c;
			--cp;
			continue;
		case 'x':	/* hexadecimal number */
			cp++;	/* skip 'x' */
			for (i = 0, c = 0;
			     isxdigit((unsigned char)*cp) && i < 2;
			     i++, cp++) {
				c <<= 4;
				if (isdigit((unsigned char)*cp))
					c |= (*cp - '0');
				else
					c |= ((toupper((unsigned char)*cp) -
					    'A') + 10);
			}
			*orig = c;
			--cp;
			continue;
		default:
			--cp;
			break;
		}
	}

	return (new);
}