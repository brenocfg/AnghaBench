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
 int /*<<< orphan*/  MCAddMsg (int,char*) ; 
 int /*<<< orphan*/  MCAddSet (int) ; 
 int /*<<< orphan*/  MCDelMsg (int) ; 
 int /*<<< orphan*/  MCDelSet (int) ; 
 int atoi (char*) ; 
 char* cskip (char*) ; 
 char* get_line (int) ; 
 char* getmsg (int,char*,char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 
 char* wskip (char*) ; 

void
MCParse(int fd)
{
	char   *cptr, *str;
	int     setid, msgid = 0;
	char    quote = 0;

	/* XXX: init sethead? */

	while ((cptr = get_line(fd))) {
		if (*cptr == '$') {
			++cptr;
			if (strncmp(cptr, "set", 3) == 0) {
				cptr += 3;
				cptr = wskip(cptr);
				setid = atoi(cptr);
				MCAddSet(setid);
				msgid = 0;
			} else if (strncmp(cptr, "delset", 6) == 0) {
				cptr += 6;
				cptr = wskip(cptr);
				setid = atoi(cptr);
				MCDelSet(setid);
			} else if (strncmp(cptr, "quote", 5) == 0) {
				cptr += 5;
				if (!*cptr)
					quote = 0;
				else {
					cptr = wskip(cptr);
					if (!*cptr)
						quote = 0;
					else
						quote = *cptr;
				}
			} else if (isspace((unsigned char) *cptr)) {
				;
			} else {
				if (*cptr) {
					cptr = wskip(cptr);
					if (*cptr)
						warning(cptr, "unrecognized line");
				}
			}
		} else {
			/*
			 * First check for (and eat) empty lines....
			 */
			if (!*cptr)
				continue;
			/*
			 * We have a digit? Start of a message. Else,
			 * syntax error.
			 */
			if (isdigit((unsigned char) *cptr)) {
				msgid = atoi(cptr);
				cptr = cskip(cptr);
				cptr = wskip(cptr);
				/* if (*cptr) ++cptr; */
			} else {
				warning(cptr, "neither blank line nor start of a message id");
				continue;
			}
			/*
			 * If we have a message ID, but no message,
			 * then this means "delete this message id
			 * from the catalog".
			 */
			if (!*cptr) {
				MCDelMsg(msgid);
			} else {
				str = getmsg(fd, cptr, quote);
				MCAddMsg(msgid, str);
			}
		}
	}
}