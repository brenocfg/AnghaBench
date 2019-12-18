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
typedef  char uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ ,int) ; 

void strexpand(char *source)
{
	uint8_t c;
	char *chr;
	char *pos;
	char d[4];

	/* Initialize position elements */
	pos = chr = source;

	/* Loop until we hit the end of the string */
	while (*pos != '\0') {
		if (*chr != '\\') {
			*pos = *chr; /* copy character to current offset */
			pos++;
			chr++;
			continue;
		}

		/* Replace the backslash with the correct character */
		switch (*++chr) {
		case 'a': *pos = '\a'; break; /* bell/alert (BEL) */
		case 'b': *pos = '\b'; break; /* backspace */
		case 'f': *pos = '\f'; break; /* form feed */
		case 'n': *pos = '\n'; break; /* new line */
		case 'r': *pos = '\r'; break; /* carriage return */
		case 't': *pos = '\t'; break; /* horizontal tab */
		case 'v': *pos = '\v'; break; /* vertical tab */
		case 'x': /* hex value (1 to 2 digits)(\xNN) */
			d[2] = '\0'; /* pre-terminate the string */

			/* verify next two characters are hex */
			d[0] = isxdigit(*(chr+1)) ? *++chr : '\0';
			if (d[0] != '\0')
				d[1] = isxdigit(*(chr+1)) ? *++chr : '\0';

			/* convert the characters to decimal */
			c = (uint8_t)strtoul(d, 0, 16);

			/* assign the converted value */
			*pos = (c != 0 || d[0] == '0') ? c : *++chr;
			break;
		case '0': /* octal value (0 to 3 digits)(\0NNN) */
			d[3] = '\0'; /* pre-terminate the string */

			/* verify next three characters are octal */
			d[0] = (isdigit(*(chr+1)) && *(chr+1) < '8') ?
			    *++chr : '\0';
			if (d[0] != '\0')
				d[1] = (isdigit(*(chr+1)) && *(chr+1) < '8') ?
				    *++chr : '\0';
			if (d[1] != '\0')
				d[2] = (isdigit(*(chr+1)) && *(chr+1) < '8') ?
				    *++chr : '\0';

			/* convert the characters to decimal */
			c = (uint8_t)strtoul(d, 0, 8);

			/* assign the converted value */
			*pos = c;
			break;
		default: /* single octal (\0..7) or unknown sequence */
			if (isdigit(*chr) && *chr < '8') {
				d[0] = *chr;
				d[1] = '\0';
				*pos = (uint8_t)strtoul(d, 0, 8);
			} else
				*pos = *chr;
		}

		/* Increment to next offset, possible next escape sequence */
		pos++;
		chr++;
	}
}