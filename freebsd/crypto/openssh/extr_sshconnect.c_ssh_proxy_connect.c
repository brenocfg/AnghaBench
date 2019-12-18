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
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 scalar_t__ dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* expand_proxy_command (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pipe (int*) ; 
 scalar_t__ proxy_command_pid ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssh_packet_set_connection (struct ssh*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ssh_proxy_connect(struct ssh *ssh, const char *host, u_short port,
    const char *proxy_command)
{
	char *command_string;
	int pin[2], pout[2];
	pid_t pid;
	char *shell;

	if ((shell = getenv("SHELL")) == NULL || *shell == '\0')
		shell = _PATH_BSHELL;

	/* Create pipes for communicating with the proxy. */
	if (pipe(pin) < 0 || pipe(pout) < 0)
		fatal("Could not create pipes to communicate with the proxy: %.100s",
		    strerror(errno));

	command_string = expand_proxy_command(proxy_command, options.user,
	    host, port);
	debug("Executing proxy command: %.500s", command_string);

	/* Fork and execute the proxy command. */
	if ((pid = fork()) == 0) {
		char *argv[10];

		/* Redirect stdin and stdout. */
		close(pin[1]);
		if (pin[0] != 0) {
			if (dup2(pin[0], 0) < 0)
				perror("dup2 stdin");
			close(pin[0]);
		}
		close(pout[0]);
		if (dup2(pout[1], 1) < 0)
			perror("dup2 stdout");
		/* Cannot be 1 because pin allocated two descriptors. */
		close(pout[1]);

		/* Stderr is left as it is so that error messages get
		   printed on the user's terminal. */
		argv[0] = shell;
		argv[1] = "-c";
		argv[2] = command_string;
		argv[3] = NULL;

		/* Execute the proxy command.  Note that we gave up any
		   extra privileges above. */
		signal(SIGPIPE, SIG_DFL);
		execv(argv[0], argv);
		perror(argv[0]);
		exit(1);
	}
	/* Parent. */
	if (pid < 0)
		fatal("fork failed: %.100s", strerror(errno));
	else
		proxy_command_pid = pid; /* save pid to clean up later */

	/* Close child side of the descriptors. */
	close(pin[0]);
	close(pout[1]);

	/* Free the command name. */
	free(command_string);

	/* Set the connection file descriptors. */
	if (ssh_packet_set_connection(ssh, pout[0], pin[1]) == NULL)
		return -1; /* ssh_packet_set_connection logs error */

	return 0;
}