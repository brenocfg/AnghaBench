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
struct ccconn {TYPE_1__* cc; int /*<<< orphan*/ * port; } ;
struct TYPE_2__ {int /*<<< orphan*/  orphaned_conns; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_log (struct ccconn*,char*,char*) ; 
 int /*<<< orphan*/  port_link ; 

void
cc_conn_rem_port(struct ccconn *conn)
{

	if (conn->port == NULL) {
		cc_conn_log(conn, "conn not on any %s", "port");
		return;
	}
	LIST_REMOVE(conn, port_link);
	conn->port = NULL;
	LIST_INSERT_HEAD(&conn->cc->orphaned_conns, conn, port_link);
}