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
struct session_state {int /*<<< orphan*/  output; int /*<<< orphan*/  connection_out; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int SSH_ERR_CONN_CLOSED ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 scalar_t__ errno ; 
 int sshbuf_consume (int /*<<< orphan*/ ,int) ; 
 int sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_ptr (int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
ssh_packet_write_poll(struct ssh *ssh)
{
	struct session_state *state = ssh->state;
	int len = sshbuf_len(state->output);
	int r;

	if (len > 0) {
		len = write(state->connection_out,
		    sshbuf_ptr(state->output), len);
		if (len == -1) {
			if (errno == EINTR || errno == EAGAIN ||
			    errno == EWOULDBLOCK)
				return 0;
			return SSH_ERR_SYSTEM_ERROR;
		}
		if (len == 0)
			return SSH_ERR_CONN_CLOSED;
		if ((r = sshbuf_consume(state->output, len)) != 0)
			return r;
	}
	return 0;
}