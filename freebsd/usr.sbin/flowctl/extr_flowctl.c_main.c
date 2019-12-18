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
typedef  int /*<<< orphan*/  sname ;

/* Variables and functions */
 int NG_NODESIZ ; 
 scalar_t__ NG_PATHSIZ ; 
 int NgMkSockNode (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NgSetDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int SORCVBUF_SIZE ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execute_command (int,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  help () ; 
 char* ng_path ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strlen (char*) ; 

int
main(int argc, char **argv)
{
	int c;
	char sname[NG_NODESIZ];
	int rcvbuf = SORCVBUF_SIZE;

	/* parse options */
	while ((c = getopt(argc, argv, "d:")) != -1) {
		switch (c) {
		case 'd':	/* set libnetgraph debug level. */
			NgSetDebug(atoi(optarg));
			break;
		}
	}

	argc -= optind;
	argv += optind;
	ng_path = argv[0];
	if (ng_path == NULL || (strlen(ng_path) > NG_PATHSIZ))
		help();
	argc--;
	argv++;

	/* create control socket. */
	snprintf(sname, sizeof(sname), "flowctl%i", getpid());

	if (NgMkSockNode(sname, &cs, NULL) == -1)
		err(1, "NgMkSockNode");

	/* set receive buffer size */
	if (setsockopt(cs, SOL_SOCKET, SO_RCVBUF, &rcvbuf, sizeof(int)) == -1)
		err(1, "setsockopt(SOL_SOCKET, SO_RCVBUF)");

	/* parse and execute command */
	execute_command(argc, argv);

	close(cs);
	
	exit(0);
}