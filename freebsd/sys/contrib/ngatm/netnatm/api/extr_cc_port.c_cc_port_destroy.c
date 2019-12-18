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
struct ccreq {int /*<<< orphan*/  addr_list; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  cookies; TYPE_1__* cc; } ;
struct ccport {int /*<<< orphan*/  addr_list; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  cookies; TYPE_1__* cc; } ;
struct ccaddr {int /*<<< orphan*/  addr_list; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  cookies; TYPE_1__* cc; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCFREE (struct ccreq*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct ccreq* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_abort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  node_link ; 
 int /*<<< orphan*/  port_link ; 

void
cc_port_destroy(struct ccport *port, int shutdown)
{
	struct ccaddr *addr;
	struct ccreq *r;

	TAILQ_REMOVE(&port->cc->port_list, port, node_link);

	while ((r = TAILQ_FIRST(&port->cookies)) != NULL) {
		TAILQ_REMOVE(&port->cookies, r, link);
		CCFREE(r);
	}

	/*
	 * Abort all connections.
	 */
	while (!LIST_EMPTY(&port->conn_list))
		cc_conn_abort(LIST_FIRST(&port->conn_list), shutdown);

	/*
	 * Free addresses.
	 */
	while ((addr = TAILQ_FIRST(&port->addr_list)) != NULL) {
		TAILQ_REMOVE(&port->addr_list, addr, port_link);
		CCFREE(addr);
	}

	CCFREE(port);
}