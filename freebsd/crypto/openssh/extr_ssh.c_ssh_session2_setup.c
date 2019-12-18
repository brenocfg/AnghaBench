#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_qos_bulk; int /*<<< orphan*/  ip_qos_interactive; scalar_t__ forward_agent; int /*<<< orphan*/  forward_x11_timeout; int /*<<< orphan*/  forward_x11_trusted; int /*<<< orphan*/  xauth_location; scalar_t__ forward_x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIRM_WARN ; 
 int /*<<< orphan*/  channel_request_start (struct ssh*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_agent_present () ; 
 int /*<<< orphan*/  client_expect_confirm (struct ssh*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_session2_setup (struct ssh*,int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ client_x11_get_proto (struct ssh*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  command ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  packet_send () ; 
 int /*<<< orphan*/  packet_set_interactive (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  subsystem_flag ; 
 int tty_flag ; 
 int /*<<< orphan*/  x11_request_forwarding_with_spoofing (struct ssh*,int,char const*,char*,char*,int) ; 

__attribute__((used)) static void
ssh_session2_setup(struct ssh *ssh, int id, int success, void *arg)
{
	extern char **environ;
	const char *display;
	int interactive = tty_flag;
	char *proto = NULL, *data = NULL;

	if (!success)
		return; /* No need for error message, channels code sens one */

	display = getenv("DISPLAY");
	if (display == NULL && options.forward_x11)
		debug("X11 forwarding requested but DISPLAY not set");
	if (options.forward_x11 && client_x11_get_proto(ssh, display,
	    options.xauth_location, options.forward_x11_trusted,
	    options.forward_x11_timeout, &proto, &data) == 0) {
		/* Request forwarding with authentication spoofing. */
		debug("Requesting X11 forwarding with authentication "
		    "spoofing.");
		x11_request_forwarding_with_spoofing(ssh, id, display, proto,
		    data, 1);
		client_expect_confirm(ssh, id, "X11 forwarding", CONFIRM_WARN);
		/* XXX exit_on_forward_failure */
		interactive = 1;
	}

	check_agent_present();
	if (options.forward_agent) {
		debug("Requesting authentication agent forwarding.");
		channel_request_start(ssh, id, "auth-agent-req@openssh.com", 0);
		packet_send();
	}

	/* Tell the packet module whether this is an interactive session. */
	packet_set_interactive(interactive,
	    options.ip_qos_interactive, options.ip_qos_bulk);

	client_session2_setup(ssh, id, tty_flag, subsystem_flag, getenv("TERM"),
	    NULL, fileno(stdin), command, environ);
}