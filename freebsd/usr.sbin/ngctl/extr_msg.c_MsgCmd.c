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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsgRead () ; 
 scalar_t__ NgSendAsciiMsg (scalar_t__,char*,char*,char*,char*) ; 
 scalar_t__ csock ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
MsgCmd(int ac, char **av)
{
	char *buf;
	char *path, *cmdstr;
	int i, len;

	/* Get arguments */
	if (ac < 3)
		return (CMDRTN_USAGE);
	path = av[1];
	cmdstr = av[2];

	/* Put command and arguments back together as one string */
	for (len = 1, i = 3; i < ac; i++)
		len += strlen(av[i]) + 1;
	if ((buf = malloc(len)) == NULL) {
		warn("malloc");
		return (CMDRTN_ERROR);
	}
	for (*buf = '\0', i = 3; i < ac; i++) {
		snprintf(buf + strlen(buf),
		    len - strlen(buf), " %s", av[i]);
	}

	/* Send it */
	if (NgSendAsciiMsg(csock, path, "%s%s", cmdstr, buf) < 0) {
		free(buf);
		warn("send msg");
		return (CMDRTN_ERROR);
	}
	free(buf);

	/* See if a synchronous reply awaits */
	{
		struct timeval tv;
		fd_set rfds;

		FD_ZERO(&rfds);
		FD_SET(csock, &rfds);
		memset(&tv, 0, sizeof(tv));
		switch (select(csock + 1, &rfds, NULL, NULL, &tv)) {
		case -1:
			err(EX_OSERR, "select");
		case 0:
			break;
		default:
			MsgRead();
			break;
		}
	}

	/* Done */
	return (CMDRTN_OK);
}