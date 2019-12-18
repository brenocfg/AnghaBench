#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct ssh {int dummy; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 scalar_t__ dup2 (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* expand_proxy_command (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int mm_receive_fd (int) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * ssh_packet_set_connection (struct ssh*,int,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ssh_proxy_fdpass_connect(struct ssh *ssh, const char *host, u_short port,
    const char *proxy_command)
{
	char *command_string;
	int sp[2], sock;
	pid_t pid;
	char *shell;

	if ((shell = getenv("SHELL")) == NULL)
		shell = _PATH_BSHELL;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sp) < 0)
		fatal("Could not create socketpair to communicate with "
		    "proxy dialer: %.100s", strerror(errno));

	command_string = expand_proxy_command(proxy_command, options.user,
	    host, port);
	debug("Executing proxy dialer command: %.500s", command_string);

	/* Fork and execute the proxy command. */
	if ((pid = fork()) == 0) {
		char *argv[10];

		close(sp[1]);
		/* Redirect stdin and stdout. */
		if (sp[0] != 0) {
			if (dup2(sp[0], 0) < 0)
				perror("dup2 stdin");
		}
		if (sp[0] != 1) {
			if (dup2(sp[0], 1) < 0)
				perror("dup2 stdout");
		}
		if (sp[0] >= 2)
			close(sp[0]);

		/*
		 * Stderr is left as it is so that error messages get
		 * printed on the user's terminal.
		 */
		argv[0] = shell;
		argv[1] = "-c";
		argv[2] = command_string;
		argv[3] = NULL;

		/*
		 * Execute the proxy command.
		 * Note that we gave up any extra privileges above.
		 */
		execv(argv[0], argv);
		perror(argv[0]);
		exit(1);
	}
	/* Parent. */
	if (pid < 0)
		fatal("fork failed: %.100s", strerror(errno));
	close(sp[0]);
	free(command_string);

	if ((sock = mm_receive_fd(sp[1])) == -1)
		fatal("proxy dialer did not pass back a connection");
	close(sp[1]);

	while (waitpid(pid, NULL, 0) == -1)
		if (errno != EINTR)
			fatal("Couldn't wait for child: %s", strerror(errno));

	/* Set the connection file descriptors. */
	if (ssh_packet_set_connection(ssh, sock, sock) == NULL)
		return -1; /* ssh_packet_set_connection logs error */

	return 0;
}