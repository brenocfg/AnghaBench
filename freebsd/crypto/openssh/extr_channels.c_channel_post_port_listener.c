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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_5__ {scalar_t__ host_port; scalar_t__ type; int /*<<< orphan*/ * path; int /*<<< orphan*/  listening_port; int /*<<< orphan*/  local_maxpacket; int /*<<< orphan*/  local_window_max; scalar_t__ notbefore; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 scalar_t__ ECONNABORTED ; 
 scalar_t__ EINTR ; 
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PORT_STREAMLOCAL ; 
 int SSH_CHANNEL_DYNAMIC ; 
 int SSH_CHANNEL_OPENING ; 
 scalar_t__ SSH_CHANNEL_RPORT_LISTENER ; 
 scalar_t__ SSH_CHANNEL_RUNIX_LISTENER ; 
 int accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 TYPE_1__* channel_new (struct ssh*,char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ monotime () ; 
 int /*<<< orphan*/  port_open_helper (struct ssh*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  set_nodelay (int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/ * xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
channel_post_port_listener(struct ssh *ssh, Channel *c,
    fd_set *readset, fd_set *writeset)
{
	Channel *nc;
	struct sockaddr_storage addr;
	int newsock, nextstate;
	socklen_t addrlen;
	char *rtype;

	if (!FD_ISSET(c->sock, readset))
		return;

	debug("Connection to port %d forwarding to %.100s port %d requested.",
	    c->listening_port, c->path, c->host_port);

	if (c->type == SSH_CHANNEL_RPORT_LISTENER) {
		nextstate = SSH_CHANNEL_OPENING;
		rtype = "forwarded-tcpip";
	} else if (c->type == SSH_CHANNEL_RUNIX_LISTENER) {
		nextstate = SSH_CHANNEL_OPENING;
		rtype = "forwarded-streamlocal@openssh.com";
	} else if (c->host_port == PORT_STREAMLOCAL) {
		nextstate = SSH_CHANNEL_OPENING;
		rtype = "direct-streamlocal@openssh.com";
	} else if (c->host_port == 0) {
		nextstate = SSH_CHANNEL_DYNAMIC;
		rtype = "dynamic-tcpip";
	} else {
		nextstate = SSH_CHANNEL_OPENING;
		rtype = "direct-tcpip";
	}

	addrlen = sizeof(addr);
	newsock = accept(c->sock, (struct sockaddr *)&addr, &addrlen);
	if (newsock < 0) {
		if (errno != EINTR && errno != EWOULDBLOCK &&
		    errno != ECONNABORTED)
			error("accept: %.100s", strerror(errno));
		if (errno == EMFILE || errno == ENFILE)
			c->notbefore = monotime() + 1;
		return;
	}
	if (c->host_port != PORT_STREAMLOCAL)
		set_nodelay(newsock);
	nc = channel_new(ssh, rtype, nextstate, newsock, newsock, -1,
	    c->local_window_max, c->local_maxpacket, 0, rtype, 1);
	nc->listening_port = c->listening_port;
	nc->host_port = c->host_port;
	if (c->path != NULL)
		nc->path = xstrdup(c->path);

	if (nextstate != SSH_CHANNEL_DYNAMIC)
		port_open_helper(ssh, nc, rtype);
}