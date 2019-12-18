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
typedef  int u_int ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {int rfd; scalar_t__ istate; scalar_t__ (* mux_rcb ) (struct ssh*,TYPE_1__*) ;int /*<<< orphan*/  self; int /*<<< orphan*/  input; scalar_t__ mux_pause; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int CHANNEL_MUX_MAX_PACKET ; 
 scalar_t__ CHAN_INPUT_OPEN ; 
 scalar_t__ CHAN_INPUT_WAIT_DRAIN ; 
 int /*<<< orphan*/  FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int PEEK_U32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_mark_dead (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  chan_rcvd_oclose (struct ssh*,TYPE_1__*) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug2 (char*,int /*<<< orphan*/ ,int,int) ; 
 int read_mux (struct ssh*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  sshbuf_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ssh*,TYPE_1__*) ; 

__attribute__((used)) static void
channel_post_mux_client_read(struct ssh *ssh, Channel *c,
    fd_set *readset, fd_set *writeset)
{
	u_int need;

	if (c->rfd == -1 || !FD_ISSET(c->rfd, readset))
		return;
	if (c->istate != CHAN_INPUT_OPEN && c->istate != CHAN_INPUT_WAIT_DRAIN)
		return;
	if (c->mux_pause)
		return;

	/*
	 * Don't not read past the precise end of packets to
	 * avoid disrupting fd passing.
	 */
	if (read_mux(ssh, c, 4) < 4) /* read header */
		return;
	/* XXX sshbuf_peek_u32 */
	need = PEEK_U32(sshbuf_ptr(c->input));
#define CHANNEL_MUX_MAX_PACKET	(256 * 1024)
	if (need > CHANNEL_MUX_MAX_PACKET) {
		debug2("channel %d: packet too big %u > %u",
		    c->self, CHANNEL_MUX_MAX_PACKET, need);
		chan_rcvd_oclose(ssh, c);
		return;
	}
	if (read_mux(ssh, c, need + 4) < need + 4) /* read body */
		return;
	if (c->mux_rcb(ssh, c) != 0) {
		debug("channel %d: mux_rcb failed", c->self);
		chan_mark_dead(ssh, c);
		return;
	}
}