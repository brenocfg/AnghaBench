#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; int sock; int /*<<< orphan*/  wfd; int /*<<< orphan*/  self; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_WR ; 
 scalar_t__ SSH_CHANNEL_LARVAL ; 
 scalar_t__ channel_close_fd (struct ssh*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug2 (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  logit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chan_shutdown_write(struct ssh *ssh, Channel *c)
{
	sshbuf_reset(c->output);
	if (c->type == SSH_CHANNEL_LARVAL)
		return;
	/* shutdown failure is allowed if write failed already */
	debug2("channel %d: close_write", c->self);
	if (c->sock != -1) {
		if (shutdown(c->sock, SHUT_WR) < 0)
			debug2("channel %d: chan_shutdown_write: "
			    "shutdown() failed for fd %d: %.100s",
			    c->self, c->sock, strerror(errno));
	} else {
		if (channel_close_fd(ssh, &c->wfd) < 0)
			logit("channel %d: chan_shutdown_write: "
			    "close() failed for fd %d: %.100s",
			    c->self, c->wfd, strerror(errno));
	}
}