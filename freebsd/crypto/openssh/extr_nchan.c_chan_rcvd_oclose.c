#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_7__ {int flags; scalar_t__ type; int ostate; int istate; int /*<<< orphan*/  self; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int CHAN_CLOSE_RCVD ; 
 int /*<<< orphan*/  CHAN_INPUT_CLOSED ; 
#define  CHAN_INPUT_OPEN 130 
#define  CHAN_INPUT_WAIT_DRAIN 129 
 int CHAN_LOCAL ; 
 int /*<<< orphan*/  CHAN_OUTPUT_CLOSED ; 
#define  CHAN_OUTPUT_OPEN 128 
 int /*<<< orphan*/  CHAN_OUTPUT_WAIT_DRAIN ; 
 scalar_t__ SSH_CHANNEL_LARVAL ; 
 int /*<<< orphan*/  chan_send_eof2 (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  chan_set_istate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_set_ostate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_shutdown_read (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  debug2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 

void
chan_rcvd_oclose(struct ssh *ssh, Channel *c)
{
	debug2("channel %d: rcvd close", c->self);
	if (!(c->flags & CHAN_LOCAL)) {
		if (c->flags & CHAN_CLOSE_RCVD)
			error("channel %d: protocol error: close rcvd twice",
			    c->self);
		c->flags |= CHAN_CLOSE_RCVD;
	}
	if (c->type == SSH_CHANNEL_LARVAL) {
		/* tear down larval channels immediately */
		chan_set_ostate(c, CHAN_OUTPUT_CLOSED);
		chan_set_istate(c, CHAN_INPUT_CLOSED);
		return;
	}
	switch (c->ostate) {
	case CHAN_OUTPUT_OPEN:
		/*
		 * wait until a data from the channel is consumed if a CLOSE
		 * is received
		 */
		chan_set_ostate(c, CHAN_OUTPUT_WAIT_DRAIN);
		break;
	}
	switch (c->istate) {
	case CHAN_INPUT_OPEN:
		chan_shutdown_read(ssh, c);
		chan_set_istate(c, CHAN_INPUT_CLOSED);
		break;
	case CHAN_INPUT_WAIT_DRAIN:
		if (!(c->flags & CHAN_LOCAL))
			chan_send_eof2(ssh, c);
		chan_set_istate(c, CHAN_INPUT_CLOSED);
		break;
	}
}