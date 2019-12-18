#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  self; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_SES_PACKET_DEFAULT ; 
 int /*<<< orphan*/  SSH_CHANNEL_LARVAL ; 
 int /*<<< orphan*/  channel_free (struct ssh*,TYPE_1__*) ; 
 TYPE_1__* channel_new (struct ssh*,char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  channel_register_cleanup (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 scalar_t__ no_more_sessions ; 
 int /*<<< orphan*/  packet_check_eom () ; 
 int /*<<< orphan*/  packet_disconnect (char*) ; 
 int /*<<< orphan*/  session_close_by_channel ; 
 int session_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_authctxt ; 

__attribute__((used)) static Channel *
server_request_session(struct ssh *ssh)
{
	Channel *c;

	debug("input_session_request");
	packet_check_eom();

	if (no_more_sessions) {
		packet_disconnect("Possible attack: attempt to open a session "
		    "after additional sessions disabled");
	}

	/*
	 * A server session has no fd to read or write until a
	 * CHANNEL_REQUEST for a shell is made, so we set the type to
	 * SSH_CHANNEL_LARVAL.  Additionally, a callback for handling all
	 * CHANNEL_REQUEST messages is registered.
	 */
	c = channel_new(ssh, "session", SSH_CHANNEL_LARVAL,
	    -1, -1, -1, /*window size*/0, CHAN_SES_PACKET_DEFAULT,
	    0, "server-session", 1);
	if (session_open(the_authctxt, c->self) != 1) {
		debug("session open failed, free channel %d", c->self);
		channel_free(ssh, c);
		return NULL;
	}
	channel_register_cleanup(ssh, c->self, session_close_by_channel, 0);
	return c;
}