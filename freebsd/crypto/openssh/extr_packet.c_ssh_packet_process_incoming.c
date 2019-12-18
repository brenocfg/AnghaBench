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
typedef  scalar_t__ u_int ;
struct ssh {struct session_state* state; } ;
struct session_state {scalar_t__ packet_discard; int /*<<< orphan*/  input; scalar_t__ keep_alive_timeouts; } ;

/* Variables and functions */
 int ssh_packet_stop_discard (struct ssh*) ; 
 int sshbuf_put (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

int
ssh_packet_process_incoming(struct ssh *ssh, const char *buf, u_int len)
{
	struct session_state *state = ssh->state;
	int r;

	if (state->packet_discard) {
		state->keep_alive_timeouts = 0; /* ?? */
		if (len >= state->packet_discard) {
			if ((r = ssh_packet_stop_discard(ssh)) != 0)
				return r;
		}
		state->packet_discard -= len;
		return 0;
	}
	if ((r = sshbuf_put(ssh->state->input, buf, len)) != 0)
		return r;

	return 0;
}