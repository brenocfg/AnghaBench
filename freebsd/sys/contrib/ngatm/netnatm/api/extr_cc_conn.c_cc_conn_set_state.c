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
struct ccconn {int state; TYPE_1__* cc; } ;
typedef  enum conn_state { ____Placeholder_conn_state } conn_state ;
struct TYPE_2__ {int log; } ;

/* Variables and functions */
 int CCLOG_CONN_STATE ; 
 int /*<<< orphan*/  cc_conn_log (struct ccconn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stab ; 

void
cc_conn_set_state(struct ccconn *conn, enum conn_state ns)
{
	if (conn->state != ns) {
		if (conn->cc->log & CCLOG_CONN_STATE)
			cc_conn_log(conn, "%s -> %s",
			    stab[conn->state], stab[ns]);
		conn->state = ns;
	}
}