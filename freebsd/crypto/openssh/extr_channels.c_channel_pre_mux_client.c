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
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_6__ {scalar_t__ istate; scalar_t__ ostate; int /*<<< orphan*/  wfd; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  rfd; int /*<<< orphan*/  mux_pause; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 scalar_t__ CHAN_INPUT_OPEN ; 
 scalar_t__ CHAN_INPUT_WAIT_DRAIN ; 
 scalar_t__ CHAN_OUTPUT_OPEN ; 
 scalar_t__ CHAN_OUTPUT_WAIT_DRAIN ; 
 int /*<<< orphan*/  CHAN_RBUF ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chan_ibuf_empty (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  chan_obuf_empty (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  chan_rcvd_oclose (struct ssh*,TYPE_1__*) ; 
 scalar_t__ sshbuf_check_reserve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
channel_pre_mux_client(struct ssh *ssh,
    Channel *c, fd_set *readset, fd_set *writeset)
{
	if (c->istate == CHAN_INPUT_OPEN && !c->mux_pause &&
	    sshbuf_check_reserve(c->input, CHAN_RBUF) == 0)
		FD_SET(c->rfd, readset);
	if (c->istate == CHAN_INPUT_WAIT_DRAIN) {
		/* clear buffer immediately (discard any partial packet) */
		sshbuf_reset(c->input);
		chan_ibuf_empty(ssh, c);
		/* Start output drain. XXX just kill chan? */
		chan_rcvd_oclose(ssh, c);
	}
	if (c->ostate == CHAN_OUTPUT_OPEN ||
	    c->ostate == CHAN_OUTPUT_WAIT_DRAIN) {
		if (sshbuf_len(c->output) > 0)
			FD_SET(c->wfd, writeset);
		else if (c->ostate == CHAN_OUTPUT_WAIT_DRAIN)
			chan_obuf_empty(ssh, c);
	}
}