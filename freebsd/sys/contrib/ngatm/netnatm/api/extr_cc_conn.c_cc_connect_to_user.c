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
struct ccuser {int /*<<< orphan*/  queue_act; int /*<<< orphan*/  connq; } ;
struct ccconn {struct ccuser* user; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_log (struct ccconn*,char*,struct ccuser*) ; 
 int /*<<< orphan*/  connq_link ; 

void
cc_connect_to_user(struct ccconn *conn, struct ccuser *user)
{

	if (conn->user != NULL)
		cc_conn_log(conn, "still connected to %p", conn->user);
	conn->user = user;
	TAILQ_INSERT_TAIL(&user->connq, conn, connq_link);
	conn->user->queue_act++;
}