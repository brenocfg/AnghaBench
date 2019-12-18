#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* isc_target; int /*<<< orphan*/  isc_target_addr; } ;
struct iscsi_daemon_request {TYPE_2__ idr_conf; } ;
struct TYPE_3__ {scalar_t__ isc_discovery; } ;
struct connection {TYPE_1__ conn_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  capsicate (struct connection*) ; 
 struct connection* connection_new (int,struct iscsi_daemon_request const*) ; 
 int /*<<< orphan*/  discovery (struct connection*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handoff (struct connection*) ; 
 int /*<<< orphan*/  log_debugx (char*) ; 
 int /*<<< orphan*/  log_set_peer_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_set_peer_name (char*) ; 
 int /*<<< orphan*/  login (struct connection*) ; 
 int /*<<< orphan*/  set_timeout (int) ; 
 int /*<<< orphan*/  setproctitle (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
handle_request(int iscsi_fd, const struct iscsi_daemon_request *request, int timeout)
{
	struct connection *conn;

	log_set_peer_addr(request->idr_conf.isc_target_addr);
	if (request->idr_conf.isc_target[0] != '\0') {
		log_set_peer_name(request->idr_conf.isc_target);
		setproctitle("%s (%s)", request->idr_conf.isc_target_addr, request->idr_conf.isc_target);
	} else {
		setproctitle("%s", request->idr_conf.isc_target_addr);
	}

	conn = connection_new(iscsi_fd, request);
	set_timeout(timeout);
	capsicate(conn);
	login(conn);
	if (conn->conn_conf.isc_discovery != 0)
		discovery(conn);
	else
		handoff(conn);

	log_debugx("nothing more to do; exiting");
	exit (0);
}