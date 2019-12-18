#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct ccport {scalar_t__ admin; int /*<<< orphan*/  conn_list; } ;
struct ccdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCPORT_RUNNING ; 
 scalar_t__ CCPORT_STOPPED ; 
 int ENOENT ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_conn_destroy (int /*<<< orphan*/ ) ; 
 struct ccport* find_port (struct ccdata*,int /*<<< orphan*/ ) ; 

int
cc_port_stop(struct ccdata *cc, u_int portno)
{
	struct ccport *port;

	if ((port = find_port(cc, portno)) == NULL)
		return (ENOENT);
	if (port->admin != CCPORT_RUNNING)
		return (ENOTCONN);

	port->admin = CCPORT_STOPPED;

	/*
	 * Abort all connections.
	 */
	while (!LIST_EMPTY(&port->conn_list))
		cc_conn_destroy(LIST_FIRST(&port->conn_list));

	return (0);
}