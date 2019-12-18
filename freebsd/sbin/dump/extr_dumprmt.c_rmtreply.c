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
typedef  int /*<<< orphan*/  emsg ;
typedef  int /*<<< orphan*/  code ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  TS_CLOSED ; 
 int atoi (char*) ; 
 int errno ; 
 int /*<<< orphan*/  msg (char*,char const*,...) ; 
 int /*<<< orphan*/  rmtconnaborted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmtgets (char*,int) ; 
 int /*<<< orphan*/  rmtstate ; 
 int strlen (char*) ; 

__attribute__((used)) static int
rmtreply(const char *cmd)
{
	char *cp;
	char code[30], emsg[BUFSIZ];

	rmtgets(code, sizeof (code));
	if (*code == 'E' || *code == 'F') {
		rmtgets(emsg, sizeof (emsg));
		msg("%s: %s", cmd, emsg);
		errno = atoi(code + 1);
		if (*code == 'F')
			rmtstate = TS_CLOSED;
		return (-1);
	}
	if (*code != 'A') {
		/* Kill trailing newline */
		cp = code + strlen(code);
		if (cp > code && *--cp == '\n')
			*cp = '\0';

		msg("Protocol to remote tape server botched (code \"%s\").\n",
		    code);
		rmtconnaborted(0);
	}
	return (atoi(code + 1));
}