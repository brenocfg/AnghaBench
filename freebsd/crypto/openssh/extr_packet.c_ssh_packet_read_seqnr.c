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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ u_char ;
struct timeval {int dummy; } ;
struct ssh {struct session_state* state; } ;
struct session_state {int packet_timeout_ms; scalar_t__ connection_in; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFDBITS ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_CONN_CLOSED ; 
 int SSH_ERR_CONN_TIMEOUT ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 scalar_t__ SSH_MSG_NONE ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  debug (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int howmany (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monotime_tv (struct timeval*) ; 
 int /*<<< orphan*/  ms_subtract_diff (struct timeval*,int*) ; 
 int /*<<< orphan*/  ms_to_timeval (struct timeval*,int) ; 
 int read (scalar_t__,char*,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int ssh_packet_process_incoming (struct ssh*,char*,int) ; 
 int ssh_packet_read_poll_seqnr (struct ssh*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int ssh_packet_write_wait (struct ssh*) ; 

int
ssh_packet_read_seqnr(struct ssh *ssh, u_char *typep, u_int32_t *seqnr_p)
{
	struct session_state *state = ssh->state;
	int len, r, ms_remain;
	fd_set *setp;
	char buf[8192];
	struct timeval timeout, start, *timeoutp = NULL;

	DBG(debug("packet_read()"));

	setp = calloc(howmany(state->connection_in + 1,
	    NFDBITS), sizeof(fd_mask));
	if (setp == NULL)
		return SSH_ERR_ALLOC_FAIL;

	/*
	 * Since we are blocking, ensure that all written packets have
	 * been sent.
	 */
	if ((r = ssh_packet_write_wait(ssh)) != 0)
		goto out;

	/* Stay in the loop until we have received a complete packet. */
	for (;;) {
		/* Try to read a packet from the buffer. */
		r = ssh_packet_read_poll_seqnr(ssh, typep, seqnr_p);
		if (r != 0)
			break;
		/* If we got a packet, return it. */
		if (*typep != SSH_MSG_NONE)
			break;
		/*
		 * Otherwise, wait for some data to arrive, add it to the
		 * buffer, and try again.
		 */
		memset(setp, 0, howmany(state->connection_in + 1,
		    NFDBITS) * sizeof(fd_mask));
		FD_SET(state->connection_in, setp);

		if (state->packet_timeout_ms > 0) {
			ms_remain = state->packet_timeout_ms;
			timeoutp = &timeout;
		}
		/* Wait for some data to arrive. */
		for (;;) {
			if (state->packet_timeout_ms != -1) {
				ms_to_timeval(&timeout, ms_remain);
				monotime_tv(&start);
			}
			if ((r = select(state->connection_in + 1, setp,
			    NULL, NULL, timeoutp)) >= 0)
				break;
			if (errno != EAGAIN && errno != EINTR &&
			    errno != EWOULDBLOCK) {
				r = SSH_ERR_SYSTEM_ERROR;
				goto out;
			}
			if (state->packet_timeout_ms == -1)
				continue;
			ms_subtract_diff(&start, &ms_remain);
			if (ms_remain <= 0) {
				r = 0;
				break;
			}
		}
		if (r == 0) {
			r = SSH_ERR_CONN_TIMEOUT;
			goto out;
		}
		/* Read data from the socket. */
		len = read(state->connection_in, buf, sizeof(buf));
		if (len == 0) {
			r = SSH_ERR_CONN_CLOSED;
			goto out;
		}
		if (len < 0) {
			r = SSH_ERR_SYSTEM_ERROR;
			goto out;
		}

		/* Append it to the buffer. */
		if ((r = ssh_packet_process_incoming(ssh, buf, len)) != 0)
			goto out;
	}
 out:
	free(setp);
	return r;
}