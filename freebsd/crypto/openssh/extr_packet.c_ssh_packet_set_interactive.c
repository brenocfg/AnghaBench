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
struct ssh {struct session_state* state; } ;
struct session_state {int set_interactive_called; int interactive_mode; int /*<<< orphan*/  connection_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_nodelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_packet_connection_is_on_socket (struct ssh*) ; 
 int /*<<< orphan*/  ssh_packet_set_tos (struct ssh*,int) ; 

void
ssh_packet_set_interactive(struct ssh *ssh, int interactive, int qos_interactive, int qos_bulk)
{
	struct session_state *state = ssh->state;

	if (state->set_interactive_called)
		return;
	state->set_interactive_called = 1;

	/* Record that we are in interactive mode. */
	state->interactive_mode = interactive;

	/* Only set socket options if using a socket.  */
	if (!ssh_packet_connection_is_on_socket(ssh))
		return;
	set_nodelay(state->connection_in);
	ssh_packet_set_tos(ssh, interactive ? qos_interactive :
	    qos_bulk);
}