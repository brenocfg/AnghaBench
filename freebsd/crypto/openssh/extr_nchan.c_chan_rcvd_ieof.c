#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_6__ {scalar_t__ ostate; int /*<<< orphan*/  output; int /*<<< orphan*/  flags; int /*<<< orphan*/  self; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_EFD_OUTPUT_ACTIVE (TYPE_1__*) ; 
 int /*<<< orphan*/  CHAN_EOF_RCVD ; 
 scalar_t__ CHAN_OUTPUT_OPEN ; 
 scalar_t__ CHAN_OUTPUT_WAIT_DRAIN ; 
 int /*<<< orphan*/  chan_obuf_empty (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  chan_set_ostate (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  debug2 (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sshbuf_len (int /*<<< orphan*/ ) ; 

void
chan_rcvd_ieof(struct ssh *ssh, Channel *c)
{
	debug2("channel %d: rcvd eof", c->self);
	c->flags |= CHAN_EOF_RCVD;
	if (c->ostate == CHAN_OUTPUT_OPEN)
		chan_set_ostate(c, CHAN_OUTPUT_WAIT_DRAIN);
	if (c->ostate == CHAN_OUTPUT_WAIT_DRAIN &&
	    sshbuf_len(c->output) == 0 &&
	    !CHANNEL_EFD_OUTPUT_ACTIVE(c))
		chan_obuf_empty(ssh, c);
}