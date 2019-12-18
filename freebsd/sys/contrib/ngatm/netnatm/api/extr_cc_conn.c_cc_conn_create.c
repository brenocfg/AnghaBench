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
struct ccdata {int log; int /*<<< orphan*/  orphaned_conns; } ;
struct ccconn {struct ccdata* cc; int /*<<< orphan*/  parties; int /*<<< orphan*/ * port; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int CCLOG_CONN_INST ; 
 struct ccconn* CCZALLOC (int) ; 
 int /*<<< orphan*/  CONN_NULL ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_log (struct ccconn*,char*,char*) ; 
 int /*<<< orphan*/  port_link ; 

struct ccconn *
cc_conn_create(struct ccdata *cc)
{
	struct ccconn *conn;

	conn = CCZALLOC(sizeof(*conn));
	if (conn == NULL)
		return (NULL);

	conn->state = CONN_NULL;
	conn->port = NULL;
	conn->cc = cc;
	LIST_INIT(&conn->parties);

	LIST_INSERT_HEAD(&cc->orphaned_conns, conn, port_link);

	if (conn->cc->log & CCLOG_CONN_INST)
		cc_conn_log(conn, "created %s", "orphaned");

	return (conn);
}