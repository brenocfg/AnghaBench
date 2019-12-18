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
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct portal {TYPE_1__* p_portal_group; } ;
struct connection {scalar_t__ conn_session_type; } ;
struct conf {scalar_t__ conf_maxproc; int /*<<< orphan*/  conf_timeout; int /*<<< orphan*/  conf_pidfh; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  host ;
struct TYPE_2__ {int /*<<< orphan*/  pg_name; struct conf* pg_conf; } ;

/* Variables and functions */
 scalar_t__ CONN_SESSION_TYPE_DISCOVERY ; 
 scalar_t__ CONN_SESSION_TYPE_NORMAL ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 struct connection* connection_new (struct portal*,int,char*,struct sockaddr const*) ; 
 int /*<<< orphan*/  discovery (struct connection*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_capsicate () ; 
 int /*<<< orphan*/  kernel_handoff (struct connection*) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_set_peer_addr (char*) ; 
 int /*<<< orphan*/  login (struct connection*) ; 
 scalar_t__ nchildren ; 
 int /*<<< orphan*/  pidfile_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setproctitle (char*,char*) ; 
 scalar_t__ wait_for_children (int) ; 

__attribute__((used)) static void
handle_connection(struct portal *portal, int fd,
    const struct sockaddr *client_sa, bool dont_fork)
{
	struct connection *conn;
	int error;
	pid_t pid;
	char host[NI_MAXHOST + 1];
	struct conf *conf;

	conf = portal->p_portal_group->pg_conf;

	if (dont_fork) {
		log_debugx("incoming connection; not forking due to -d flag");
	} else {
		nchildren -= wait_for_children(false);
		assert(nchildren >= 0);

		while (conf->conf_maxproc > 0 && nchildren >= conf->conf_maxproc) {
			log_debugx("maxproc limit of %d child processes hit; "
			    "waiting for child process to exit", conf->conf_maxproc);
			nchildren -= wait_for_children(true);
			assert(nchildren >= 0);
		}
		log_debugx("incoming connection; forking child process #%d",
		    nchildren);
		nchildren++;
		pid = fork();
		if (pid < 0)
			log_err(1, "fork");
		if (pid > 0) {
			close(fd);
			return;
		}
	}
	pidfile_close(conf->conf_pidfh);

	error = getnameinfo(client_sa, client_sa->sa_len,
	    host, sizeof(host), NULL, 0, NI_NUMERICHOST);
	if (error != 0)
		log_errx(1, "getnameinfo: %s", gai_strerror(error));

	log_debugx("accepted connection from %s; portal group \"%s\"",
	    host, portal->p_portal_group->pg_name);
	log_set_peer_addr(host);
	setproctitle("%s", host);

	conn = connection_new(portal, fd, host, client_sa);
	set_timeout(conf->conf_timeout, true);
	kernel_capsicate();
	login(conn);
	if (conn->conn_session_type == CONN_SESSION_TYPE_NORMAL) {
		kernel_handoff(conn);
		log_debugx("connection handed off to the kernel");
	} else {
		assert(conn->conn_session_type == CONN_SESSION_TYPE_DISCOVERY);
		discovery(conn);
	}
	log_debugx("nothing more to do; exiting");
	exit(0);
}