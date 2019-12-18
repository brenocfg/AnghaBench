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
typedef  scalar_t__ u_int ;
struct ccreq {struct ccconn* conn; } ;
struct ccport {scalar_t__ admin; int /*<<< orphan*/  cookies; } ;
struct ccconn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCFREE (struct ccreq*) ; 
 scalar_t__ CCPORT_RUNNING ; 
 int /*<<< orphan*/  CONN_SIG_ERROR ; 
 int /*<<< orphan*/  CONN_SIG_OK ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccreq*,int /*<<< orphan*/ ) ; 
 scalar_t__ UNIAPI_OK ; 
 int cc_conn_resp (struct ccconn*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cc_port_log (struct ccport*,char*,scalar_t__) ; 
 struct ccreq* find_cookie (struct ccport*,scalar_t__) ; 
 int /*<<< orphan*/  link ; 

int
cc_uni_response(struct ccport *port, u_int cookie, u_int reason, u_int state)
{
	struct ccconn *conn;
	struct ccreq *req;

	if (cookie == 0)
		return (EINVAL);

	if (port->admin != CCPORT_RUNNING)
		return (ENOTCONN);

	if ((req = find_cookie(port, cookie)) == NULL) {
		cc_port_log(port, "UNI response for unknown cookie %u", cookie);
		return (EINVAL);
	}
	conn = req->conn;

	TAILQ_REMOVE(&port->cookies, req, link);
	CCFREE(req);

	if (reason == UNIAPI_OK)
		return (cc_conn_resp(conn, CONN_SIG_OK,
		    cookie, reason, state));
	else
		return (cc_conn_resp(conn, CONN_SIG_ERROR,
		    cookie, reason, state));
}