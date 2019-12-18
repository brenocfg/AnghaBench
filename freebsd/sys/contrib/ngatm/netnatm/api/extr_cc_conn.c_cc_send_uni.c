#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct uni_msg {int dummy; } ;
struct ccreq {scalar_t__ cookie; struct ccconn* conn; int /*<<< orphan*/  req; } ;
struct ccconn {TYPE_3__* port; } ;
struct TYPE_6__ {int /*<<< orphan*/  uarg; TYPE_2__* cc; int /*<<< orphan*/  cookies; } ;
struct TYPE_5__ {scalar_t__ cookie; TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_uni ) (struct ccconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct uni_msg*) ;} ;

/* Variables and functions */
 struct ccreq* CCZALLOC (int) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ccreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_log (struct ccconn*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  stub1 (struct ccconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct uni_msg*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

__attribute__((used)) static void
cc_send_uni(struct ccconn *conn, u_int op, struct uni_msg *msg)
{
	struct ccreq *r;

	r = CCZALLOC(sizeof(*r));
	if (r == NULL) {
		if (msg != NULL)
			uni_msg_destroy(msg);
		cc_conn_log(conn, "no memory for cookie op=%u", op);
		return;
	}

	if ((r->cookie = ++conn->port->cc->cookie) == 0)
		r->cookie = ++conn->port->cc->cookie;
	r->req = op;
	r->conn = conn;

	TAILQ_INSERT_TAIL(&conn->port->cookies, r, link);

	conn->port->cc->funcs->send_uni(conn, conn->port->uarg, op,
	    r->cookie, msg);
}