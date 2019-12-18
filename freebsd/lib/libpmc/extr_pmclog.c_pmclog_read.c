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
struct pmclog_parse_state {scalar_t__ ps_state; scalar_t__ ps_len; int ps_fd; int /*<<< orphan*/  ps_data; int /*<<< orphan*/  ps_buffer; } ;
struct pmclog_ev {scalar_t__ pl_state; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ PL_STATE_ERROR ; 
 int /*<<< orphan*/  PMCLOG_BUFFER_SIZE ; 
 scalar_t__ PMCLOG_EOF ; 
 void* PMCLOG_ERROR ; 
 int PMCLOG_FD_NONE ; 
 scalar_t__ PMCLOG_REQUIRE_DATA ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int pmclog_get_event (struct pmclog_parse_state*,int /*<<< orphan*/ *,scalar_t__*,struct pmclog_ev*) ; 
 scalar_t__ read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pmclog_read(void *cookie, struct pmclog_ev *ev)
{
	int retval;
	ssize_t nread;
	struct pmclog_parse_state *ps;

	ps = (struct pmclog_parse_state *) cookie;

	if (ps->ps_state == PL_STATE_ERROR) {
		ev->pl_state = PMCLOG_ERROR;
		return -1;
	}

	/*
	 * If there isn't enough data left for a new event try and get
	 * more data.
	 */
	if (ps->ps_len == 0) {
		ev->pl_state = PMCLOG_REQUIRE_DATA;

		/*
		 * If we have a valid file descriptor to read from, attempt
		 * to read from that.  This read may return with an error,
		 * (which may be EAGAIN or other recoverable error), or
		 * can return EOF.
		 */
		if (ps->ps_fd != PMCLOG_FD_NONE) {
		refill:
			nread = read(ps->ps_fd, ps->ps_buffer,
			    PMCLOG_BUFFER_SIZE);

			if (nread <= 0) {
				if (nread == 0)
					ev->pl_state = PMCLOG_EOF;
				else if (errno != EAGAIN) /* not restartable */
					ev->pl_state = PMCLOG_ERROR;
				return -1;
			}

			ps->ps_len = nread;
			ps->ps_data = ps->ps_buffer;
		} else {
			return -1;
		}
	}

	assert(ps->ps_len > 0);


	 /* Retrieve one event from the byte stream. */
	retval = pmclog_get_event(ps, &ps->ps_data, &ps->ps_len, ev);
	/*
	 * If we need more data and we have a configured fd, try read
	 * from it.
	 */
	if (retval < 0 && ev->pl_state == PMCLOG_REQUIRE_DATA &&
	    ps->ps_fd != -1) {
		assert(ps->ps_len == 0);
		goto refill;
	}

	return retval;
}