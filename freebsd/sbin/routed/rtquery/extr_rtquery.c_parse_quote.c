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

__attribute__((used)) static int				/* -1=bad */
parse_quote(char **linep,
	    const char *delims,
	    char *delimp,
	    char *buf,
	    int	lim)
{
	char c, *pc;
	const char *p;


	pc = *linep;
	if (*pc == '\0')
		return -1;

	for (;;) {
		if (lim == 0)
			return -1;
		c = *pc++;
		if (c == '\0')
			break;

		if (c == '\\' && *pc != '\0') {
			if ((c = *pc++) == 'n') {
				c = '\n';
			} else if (c == 'r') {
				c = '\r';
			} else if (c == 't') {
				c = '\t';
			} else if (c == 'b') {
				c = '\b';
			} else if (c >= '0' && c <= '7') {
				c -= '0';
				if (*pc >= '0' && *pc <= '7') {
					c = (c<<3)+(*pc++ - '0');
					if (*pc >= '0' && *pc <= '7')
					    c = (c<<3)+(*pc++ - '0');
				}
			}

		} else {
			for (p = delims; *p != '\0'; ++p) {
				if (*p == c)
					goto exit;
			}
		}

		*buf++ = c;
		--lim;
	}
exit:
	if (delimp != NULL)
		*delimp = c;
	*linep = pc-1;
	if (lim != 0)
		*buf = '\0';
	return 0;
}