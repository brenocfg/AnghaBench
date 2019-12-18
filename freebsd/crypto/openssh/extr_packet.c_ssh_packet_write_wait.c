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
struct timeval {int dummy; } ;
struct ssh {struct session_state* state; } ;
struct session_state {int packet_timeout_ms; scalar_t__ connection_out; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFDBITS ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_CONN_TIMEOUT ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int howmany (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monotime_tv (struct timeval*) ; 
 int /*<<< orphan*/  ms_subtract_diff (struct timeval*,int*) ; 
 int /*<<< orphan*/  ms_to_timeval (struct timeval*,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ ssh_packet_have_data_to_write (struct ssh*) ; 
 int ssh_packet_write_poll (struct ssh*) ; 

int
ssh_packet_write_wait(struct ssh *ssh)
{
	fd_set *setp;
	int ret, r, ms_remain = 0;
	struct timeval start, timeout, *timeoutp = NULL;
	struct session_state *state = ssh->state;

	setp = calloc(howmany(state->connection_out + 1,
	    NFDBITS), sizeof(fd_mask));
	if (setp == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = ssh_packet_write_poll(ssh)) != 0) {
		free(setp);
		return r;
	}
	while (ssh_packet_have_data_to_write(ssh)) {
		memset(setp, 0, howmany(state->connection_out + 1,
		    NFDBITS) * sizeof(fd_mask));
		FD_SET(state->connection_out, setp);

		if (state->packet_timeout_ms > 0) {
			ms_remain = state->packet_timeout_ms;
			timeoutp = &timeout;
		}
		for (;;) {
			if (state->packet_timeout_ms != -1) {
				ms_to_timeval(&timeout, ms_remain);
				monotime_tv(&start);
			}
			if ((ret = select(state->connection_out + 1,
			    NULL, setp, NULL, timeoutp)) >= 0)
				break;
			if (errno != EAGAIN && errno != EINTR &&
			    errno != EWOULDBLOCK)
				break;
			if (state->packet_timeout_ms == -1)
				continue;
			ms_subtract_diff(&start, &ms_remain);
			if (ms_remain <= 0) {
				ret = 0;
				break;
			}
		}
		if (ret == 0) {
			free(setp);
			return SSH_ERR_CONN_TIMEOUT;
		}
		if ((r = ssh_packet_write_poll(ssh)) != 0) {
			free(setp);
			return r;
		}
	}
	free(setp);
	return 0;
}