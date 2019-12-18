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
 char* RSH_PROGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ doencrypt ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 scalar_t__ eflag ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 scalar_t__ forwardtkt ; 
 scalar_t__ noencrypt ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pipe (int*) ; 
 char* port ; 
 scalar_t__ usebroken ; 
 scalar_t__ usekrb4 ; 
 scalar_t__ usekrb5 ; 

int
do_cmd(char *host, char *remuser, char *cmd, int *fdin, int *fdout)
{
	int pin[2], pout[2], reserved[2];

	/*
	 * Reserve two descriptors so that the real pipes won't get
	 * descriptors 0 and 1 because that will screw up dup2 below.
	 */
	pipe(reserved);

	/* Create a socket pair for communicating with rsh. */
	if (pipe(pin) < 0) {
		perror("pipe");
		exit(255);
	}
	if (pipe(pout) < 0) {
		perror("pipe");
		exit(255);
	}

	/* Free the reserved descriptors. */
	close(reserved[0]);
	close(reserved[1]);

	/* For a child to execute the command on the remote host using rsh. */
	if (fork() == 0) {
		char *args[100];
		unsigned int i;

		/* Child. */
		close(pin[1]);
		close(pout[0]);
		dup2(pin[0], 0);
		dup2(pout[1], 1);
		close(pin[0]);
		close(pout[1]);

		i = 0;
		args[i++] = RSH_PROGRAM;
		if (usekrb4)
			args[i++] = "-4";
		if (usekrb5)
			args[i++] = "-5";
		if (usebroken)
			args[i++] = "-K";
		if (doencrypt)
			args[i++] = "-x";
		if (forwardtkt)
			args[i++] = "-F";
		if (noencrypt)
			args[i++] = "-z";
		if (port != NULL) {
			args[i++] = "-p";
			args[i++] = port;
		}
		if (eflag)
		    args[i++] = "-e";
		if (remuser != NULL) {
			args[i++] = "-l";
			args[i++] = remuser;
		}
		args[i++] = host;
		args[i++] = cmd;
		args[i++] = NULL;

		execvp(RSH_PROGRAM, args);
		perror(RSH_PROGRAM);
		exit(1);
	}
	/* Parent.  Close the other side, and return the local side. */
	close(pin[0]);
	*fdout = pin[1];
	close(pout[1]);
	*fdin = pout[0];
	return 0;
}