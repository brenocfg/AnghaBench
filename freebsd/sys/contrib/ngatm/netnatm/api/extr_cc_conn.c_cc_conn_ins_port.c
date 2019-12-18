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
struct TYPE_2__ {int /*<<< orphan*/  port; } ;
struct ccport {int /*<<< orphan*/  conn_list; TYPE_1__ param; } ;
struct ccconn {struct ccport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_log (struct ccconn*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_rem_port (struct ccconn*) ; 
 int /*<<< orphan*/  port_link ; 

void
cc_conn_ins_port(struct ccconn *conn, struct ccport *port)
{

	if (conn->port != NULL) {
		cc_conn_log(conn, "conn is already on port %u",
		    conn->port->param.port);
		cc_conn_rem_port(conn);
	}
	LIST_REMOVE(conn, port_link);

	conn->port = port;
	LIST_INSERT_HEAD(&port->conn_list, conn, port_link);

}