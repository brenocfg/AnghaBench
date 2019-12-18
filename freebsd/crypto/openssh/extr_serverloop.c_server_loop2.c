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
typedef  int u_int64_t ;
typedef  int u_int ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {scalar_t__ rekey_interval; } ;
typedef  int /*<<< orphan*/  Authctxt ;

/* Variables and functions */
 int MAXIMUM (int,int) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  channel_after_select (struct ssh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_free_all (struct ssh*) ; 
 int /*<<< orphan*/  channel_output_poll (struct ssh*) ; 
 scalar_t__ child_terminated ; 
 int /*<<< orphan*/  cleanup_exit (int) ; 
 int /*<<< orphan*/  collect_children (struct ssh*) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logit (char*,int) ; 
 int* notify_pipe ; 
 int /*<<< orphan*/  notify_setup () ; 
 TYPE_1__ options ; 
 int packet_get_connection_in () ; 
 int packet_get_connection_out () ; 
 int packet_get_rekey_timeout () ; 
 scalar_t__ packet_not_very_much_data_to_write () ; 
 int /*<<< orphan*/  process_buffered_input_packets (struct ssh*) ; 
 scalar_t__ process_input (struct ssh*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  process_output (int /*<<< orphan*/ *,int) ; 
 scalar_t__ received_sigterm ; 
 int /*<<< orphan*/  server_init_dispatch () ; 
 int /*<<< orphan*/  session_destroy_all (struct ssh*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigchld_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  ssh_packet_is_rekeying (struct ssh*) ; 
 int /*<<< orphan*/  use_privsep ; 
 int /*<<< orphan*/  wait_until_can_do_something (struct ssh*,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*,int*,int) ; 

void
server_loop2(struct ssh *ssh, Authctxt *authctxt)
{
	fd_set *readset = NULL, *writeset = NULL;
	int max_fd;
	u_int nalloc = 0, connection_in, connection_out;
	u_int64_t rekey_timeout_ms = 0;

	debug("Entering interactive session for SSH2.");

	signal(SIGCHLD, sigchld_handler);
	child_terminated = 0;
	connection_in = packet_get_connection_in();
	connection_out = packet_get_connection_out();

	if (!use_privsep) {
		signal(SIGTERM, sigterm_handler);
		signal(SIGINT, sigterm_handler);
		signal(SIGQUIT, sigterm_handler);
	}

	notify_setup();

	max_fd = MAXIMUM(connection_in, connection_out);
	max_fd = MAXIMUM(max_fd, notify_pipe[0]);

	server_init_dispatch();

	for (;;) {
		process_buffered_input_packets(ssh);

		if (!ssh_packet_is_rekeying(ssh) &&
		    packet_not_very_much_data_to_write())
			channel_output_poll(ssh);
		if (options.rekey_interval > 0 && !ssh_packet_is_rekeying(ssh))
			rekey_timeout_ms = packet_get_rekey_timeout() * 1000;
		else
			rekey_timeout_ms = 0;

		wait_until_can_do_something(ssh, connection_in, connection_out,
		    &readset, &writeset, &max_fd, &nalloc, rekey_timeout_ms);

		if (received_sigterm) {
			logit("Exiting on signal %d", (int)received_sigterm);
			/* Clean up sessions, utmp, etc. */
			cleanup_exit(255);
		}

		collect_children(ssh);
		if (!ssh_packet_is_rekeying(ssh))
			channel_after_select(ssh, readset, writeset);
		if (process_input(ssh, readset, connection_in) < 0)
			break;
		process_output(writeset, connection_out);
	}
	collect_children(ssh);

	free(readset);
	free(writeset);

	/* free all channels, no more reads and writes */
	channel_free_all(ssh);

	/* free remaining sessions, e.g. remove wtmp entries */
	session_destroy_all(ssh, NULL);
}