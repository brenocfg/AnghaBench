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

__attribute__((used)) static int
escape(char *fmt, int percent, size_t *len)
{
	char *save, *store, c;
	int value;

	for (save = store = fmt; ((c = *fmt) != 0); ++fmt, ++store) {
		if (c != '\\') {
			*store = c;
			continue;
		}
		switch (*++fmt) {
		case '\0':		/* EOS, user error */
			*store = '\\';
			*++store = '\0';
			*len = store - save;
			return (0);
		case '\\':		/* backslash */
		case '\'':		/* single quote */
			*store = *fmt;
			break;
		case 'a':		/* bell/alert */
			*store = '\a';
			break;
		case 'b':		/* backspace */
			*store = '\b';
			break;
		case 'c':
			if (!percent) {
				*store = '\0';
				*len = store - save;
				return (1);
			}
			*store = 'c';
			break;
		case 'f':		/* form-feed */
			*store = '\f';
			break;
		case 'n':		/* newline */
			*store = '\n';
			break;
		case 'r':		/* carriage-return */
			*store = '\r';
			break;
		case 't':		/* horizontal tab */
			*store = '\t';
			break;
		case 'v':		/* vertical tab */
			*store = '\v';
			break;
					/* octal constant */
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			c = (!percent && *fmt == '0') ? 4 : 3;
			for (value = 0;
			    c-- && *fmt >= '0' && *fmt <= '7'; ++fmt) {
				value <<= 3;
				value += *fmt - '0';
			}
			--fmt;
			if (percent && value == '%') {
				*store++ = '%';
				*store = '%';
			} else
				*store = (char)value;
			break;
		default:
			*store = *fmt;
			break;
		}
	}
	*store = '\0';
	*len = store - save;
	return (0);
}