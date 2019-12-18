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
 int /*<<< orphan*/  CASEOF (char,char) ; 
 int /*<<< orphan*/  error (char*) ; 
 char* get_line (int) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 long strlen (char*) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 
 scalar_t__* wskip (char*) ; 
 char* xmalloc (long) ; 
 char* xrealloc (char*,long) ; 

__attribute__((used)) static char *
getmsg(int fd, char *cptr, char quote)
{
	static char *msg = NULL;
	static long msglen = 0;
	long    clen, i;
	char   *tptr;

	if (quote && *cptr == quote) {
		++cptr;
	} 

	clen = strlen(cptr) + 1;
	if (clen > msglen) {
		if (msglen)
			msg = xrealloc(msg, clen);
		else
			msg = xmalloc(clen);
		msglen = clen;
	}
	tptr = msg;

	while (*cptr) {
		if (quote && *cptr == quote) {
			char   *tmp;
			tmp = cptr + 1;
			if (*tmp && (!isspace((unsigned char) *tmp) || *wskip(tmp))) {
				warning(cptr, "unexpected quote character, ignoring");
				*tptr++ = *cptr++;
			} else {
				*cptr = '\0';
			}
		} else
			if (*cptr == '\\') {
				++cptr;
				switch (*cptr) {
				case '\0':
					cptr = get_line(fd);
					if (!cptr)
						error("premature end of file");
					msglen += strlen(cptr);
					i = tptr - msg;
					msg = xrealloc(msg, msglen);
					tptr = msg + i;
					break;

		#define	CASEOF(CS, CH)		\
			case CS:		\
				*tptr++ = CH;	\
				++cptr;		\
				break;		\

				CASEOF('n', '\n');
				CASEOF('t', '\t');
				CASEOF('v', '\v');
				CASEOF('b', '\b');
				CASEOF('r', '\r');
				CASEOF('f', '\f');
				CASEOF('"', '"');
				CASEOF('\\', '\\');

				default:
					if (quote && *cptr == quote) {
						*tptr++ = *cptr++;
					} else if (isdigit((unsigned char) *cptr)) {
						*tptr = 0;
						for (i = 0; i < 3; ++i) {
							if (!isdigit((unsigned char) *cptr))
								break;
							if (*cptr > '7')
								warning(cptr, "octal number greater than 7?!");
							*tptr *= 8;
							*tptr += (*cptr - '0');
							++cptr;
						}
					} else {
						warning(cptr, "unrecognized escape sequence");
					}
					break;
				}
			} else {
				*tptr++ = *cptr++;
			}
	}
	*tptr = '\0';
	return (msg);
}