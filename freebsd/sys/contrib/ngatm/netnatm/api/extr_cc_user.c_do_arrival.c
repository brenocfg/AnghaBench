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
struct ccuser {int /*<<< orphan*/  connq; scalar_t__ aborted; } ;
struct ccconn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMOP_ARRIVAL_OF_INCOMING_CALL ; 
 int /*<<< orphan*/  CONN_SIG_ARRIVAL ; 
 struct ccconn* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USER_IN_ARRIVED ; 
 int /*<<< orphan*/  cc_conn_sig (struct ccconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_user_send (struct ccuser*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_state (struct ccuser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_arrival(struct ccuser *user)
{
	struct ccconn *conn;

	user->aborted = 0;
	if ((conn = TAILQ_FIRST(&user->connq)) != NULL) {
		set_state(user, USER_IN_ARRIVED);
		cc_user_send(user, ATMOP_ARRIVAL_OF_INCOMING_CALL, NULL, 0);
		cc_conn_sig(conn, CONN_SIG_ARRIVAL, NULL);
	}
}