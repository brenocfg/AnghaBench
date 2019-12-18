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
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {int /*<<< orphan*/  ostate; int /*<<< orphan*/  istate; int /*<<< orphan*/  self; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_CHANNEL_OPEN ; 
 int /*<<< orphan*/  chan_ibuf_empty (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  chan_read_failed (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  chan_write_failed (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  channel_pre_open (struct ssh*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logit (char*) ; 
 int /*<<< orphan*/  sshbuf_reset (int /*<<< orphan*/ ) ; 
 int x11_open_helper (struct ssh*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
channel_pre_x11_open(struct ssh *ssh, Channel *c,
    fd_set *readset, fd_set *writeset)
{
	int ret = x11_open_helper(ssh, c->output);

	/* c->force_drain = 1; */

	if (ret == 1) {
		c->type = SSH_CHANNEL_OPEN;
		channel_pre_open(ssh, c, readset, writeset);
	} else if (ret == -1) {
		logit("X11 connection rejected because of wrong authentication.");
		debug2("X11 rejected %d i%d/o%d",
		    c->self, c->istate, c->ostate);
		chan_read_failed(ssh, c);
		sshbuf_reset(c->input);
		chan_ibuf_empty(ssh, c);
		sshbuf_reset(c->output);
		chan_write_failed(ssh, c);
		debug2("X11 closed %d i%d/o%d", c->self, c->istate, c->ostate);
	}
}