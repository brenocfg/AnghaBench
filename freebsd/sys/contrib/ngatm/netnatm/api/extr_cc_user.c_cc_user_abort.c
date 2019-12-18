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
struct uni_ie_cause {int dummy; } ;
struct ccuser {int /*<<< orphan*/  connq; int /*<<< orphan*/  aborted; } ;
struct ccconn {struct uni_ie_cause* cause; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_SIG_USER_ABORT ; 
 struct ccconn* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USER_NULL ; 
 int /*<<< orphan*/  cc_conn_dispatch (struct ccconn*) ; 
 int /*<<< orphan*/  cc_conn_reset_acceptor (struct ccconn*) ; 
 int /*<<< orphan*/  cc_conn_sig (struct ccconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_disconnect_from_user (struct ccconn*) ; 
 int /*<<< orphan*/  cc_user_reset (struct ccuser*) ; 
 int /*<<< orphan*/  memset (struct uni_ie_cause*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_state (struct ccuser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cc_user_abort(struct ccuser *user, const struct uni_ie_cause *cause)
{
	struct ccconn *conn;

	/*
	 * Although the standard state that 'all connections
	 * associated with this endpoint are aborted' we only
	 * have to abort the head one, because in state A6
	 * (call present) the endpoint is only associated to the
	 * head connection - the others are 'somewhere else' and
	 * need to be redispatched.
	 *
	 * First bring user into a state that the connections
	 * are not dispatched back to it.
	 */
	set_state(user, USER_NULL);
	if (!user->aborted) {
		if ((conn = TAILQ_FIRST(&user->connq)) != NULL) {
			memset(conn->cause, 0, sizeof(conn->cause));
			if (cause != NULL)
				conn->cause[0] = *cause;
			cc_conn_reset_acceptor(conn);
			cc_disconnect_from_user(conn);
			cc_conn_sig(conn, CONN_SIG_USER_ABORT, NULL);
		}
	}

	while ((conn = TAILQ_FIRST(&user->connq)) != NULL) {
		/* these should be in C21 */
		cc_disconnect_from_user(conn);
		cc_conn_dispatch(conn);
	}

	cc_user_reset(user);
}