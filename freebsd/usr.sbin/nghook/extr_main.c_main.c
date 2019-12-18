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
typedef  int /*<<< orphan*/  u_char ;
struct ngm_connect {int /*<<< orphan*/  peerhook; int /*<<< orphan*/  ourhook; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  ngc ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUF_SIZE ; 
 char* DEFAULT_HOOKNAME ; 
 int /*<<< orphan*/  EX_OSERR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGM_CONNECT ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 char* NG_SOCK_HOOK_NAME ; 
 scalar_t__ NgMkSockNode (int /*<<< orphan*/ *,int*,int*) ; 
 int NgRecvData (int,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NgSendData (int,char*,char*,int) ; 
 scalar_t__ NgSendMsg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ngm_connect*,int) ; 
 int /*<<< orphan*/  NgSetDebug (int) ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  WriteAscii (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int infd ; 
 int /*<<< orphan*/ * msgs ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  outfd ; 
 int read (int,char*,int) ; 
 scalar_t__ select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_msgs (int,char const*) ; 
 int sl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sl_init () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
main(int ac, char *av[])
{
	struct ngm_connect ngc;
	const char *path = NULL;
	const char *hook = DEFAULT_HOOKNAME;
	int     csock, dsock;
	int     asciiFlag = 0;
	int     loopFlag = 0;
	int	noInput = 0;
	int	execFlag = 0;
	int	ch;

	if ((msgs = sl_init()) == NULL)
		err(EX_OSERR, NULL);

	/* Parse flags */
	while ((ch = getopt(ac, av, "aedlm:nsS")) != -1) {
		switch (ch) {
		case 'a':
			asciiFlag = 1;
			break;
		case 'd':
			NgSetDebug(NgSetDebug(-1) + 1);
			break;
		case 'e':
			execFlag = 1;
			break;
		case 'l':
			loopFlag = 1;
			break;
		case 'n':
			noInput = 1;
			break;
		case 'm':
			if (sl_add(msgs, optarg) == -1)
				err(EX_OSERR, NULL);
			break;
		case 's':
			outfd = STDIN_FILENO;
			break;
		case 'S':
			infd = STDOUT_FILENO;
			break;
		case '?':
		default:
			Usage();
		}
	}
	ac -= optind;
	av += optind;

	if (execFlag) {
		if (asciiFlag || loopFlag) {
			fprintf(stderr, "conflicting options\n");
			Usage();
		}
		if (ac < 3)
			Usage();
		path = av[0];
		hook = av[1];
		av += 2;
		ac -= 2;
	} else {
		/* Get params */
		switch (ac) {
		case 2:
			hook = av[1];
			/* FALLTHROUGH */
		case 1:
			path = av[0];
			break;
		default:
			Usage();
		}
	}

	/* Get sockets */
	if (NgMkSockNode(NULL, &csock, &dsock) < 0)
		errx(EX_OSERR, "can't get sockets");

	/* Connect socket node to specified node */
	snprintf(ngc.path, sizeof(ngc.path), "%s", path);
	snprintf(ngc.ourhook, sizeof(ngc.ourhook), NG_SOCK_HOOK_NAME);
	snprintf(ngc.peerhook, sizeof(ngc.peerhook), "%s", hook);

	if (NgSendMsg(csock, ".",
	    NGM_GENERIC_COOKIE, NGM_CONNECT, &ngc, sizeof(ngc)) < 0)
		errx(EX_OSERR, "can't connect to node");

	if (execFlag) {
		/* move dsock to fd 0 and 1 */
		(void)close(0);
		(void)close(1);
		if (!noInput)
			(void)dup2(dsock, 0);
		(void)dup2(dsock, 1);

		send_msgs(csock, path);

		/* try executing the program */
		(void)execv(av[0], av);
		err(EX_OSERR, "%s", av[0]);

	} else
		send_msgs(csock, path);

	/* Close standard input if not reading from it */
	if (noInput)
		fclose(stdin);

	/* Relay data */
	while (1) {
		fd_set  rfds;

		/* Setup bits */
		FD_ZERO(&rfds);
		if (!noInput)
			FD_SET(infd, &rfds);
		FD_SET(dsock, &rfds);

		/* Wait for something to happen */
		if (select(FD_SETSIZE, &rfds, NULL, NULL, NULL) < 0)
			err(EX_OSERR, "select");

		/* Check data from socket */
		if (FD_ISSET(dsock, &rfds)) {
			char    buf[BUF_SIZE];
			int     rl, wl;

			/* Read packet from socket */
			if ((rl = NgRecvData(dsock,
			    buf, sizeof(buf), NULL)) < 0)
				err(EX_OSERR, "read(hook)");
			if (rl == 0)
				errx(EX_OSERR, "read EOF from hook?!");

			/* Write packet to stdout */
			if (asciiFlag)
				WriteAscii((u_char *) buf, rl);
			else if ((wl = write(outfd, buf, rl)) != rl) {
				if (wl < 0) {
					err(EX_OSERR, "write(stdout)");
				} else {
					errx(EX_OSERR,
					    "stdout: read %d, wrote %d",
					    rl, wl);
				}
			}
			/* Loopback */
			if (loopFlag) {
				if (NgSendData(dsock, NG_SOCK_HOOK_NAME, buf, rl) < 0)
					err(EX_OSERR, "write(hook)");
			}
		}

		/* Check data from stdin */
		if (FD_ISSET(infd, &rfds)) {
			char    buf[BUF_SIZE];
			int     rl;

			/* Read packet from stdin */
			if ((rl = read(infd, buf, sizeof(buf))) < 0)
				err(EX_OSERR, "read(stdin)");
			if (rl == 0)
				errx(EX_OSERR, "EOF(stdin)");

			/* Write packet to socket */
			if (NgSendData(dsock, NG_SOCK_HOOK_NAME, buf, rl) < 0)
				err(EX_OSERR, "write(hook)");
		}
	}
}