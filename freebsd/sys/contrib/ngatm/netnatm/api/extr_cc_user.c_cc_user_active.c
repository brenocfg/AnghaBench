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
struct ccuser {int /*<<< orphan*/  config; int /*<<< orphan*/  connq; } ;
struct TYPE_2__ {scalar_t__ cfg; } ;
struct ccconn {int /*<<< orphan*/  connid; TYPE_1__ bearer; } ;
struct atm_p2p_call_active {int /*<<< orphan*/  connid; } ;
struct atm_p2mp_call_active {int /*<<< orphan*/  connid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMOP_P2MP_CALL_ACTIVE ; 
 int /*<<< orphan*/  ATMOP_P2P_CALL_ACTIVE ; 
 int /*<<< orphan*/  CCFREE (struct atm_p2p_call_active*) ; 
 struct atm_p2p_call_active* CCZALLOC (int) ; 
 struct ccconn* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ UNI_BEARER_P2P ; 
 int /*<<< orphan*/  USER_ACTIVE ; 
 int /*<<< orphan*/  USER_P2P ; 
 int /*<<< orphan*/  USER_ROOT ; 
 int /*<<< orphan*/  cc_user_send (struct ccuser*,int /*<<< orphan*/ ,struct atm_p2p_call_active*,int) ; 
 int /*<<< orphan*/  set_state (struct ccuser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cc_user_active(struct ccuser *user)
{
	struct ccconn *conn = TAILQ_FIRST(&user->connq);

	set_state(user, USER_ACTIVE);
	if (conn->bearer.cfg == UNI_BEARER_P2P) {
		struct atm_p2p_call_active *act;

		user->config = USER_P2P;
		act = CCZALLOC(sizeof(*act));
		if (act == NULL)
			return;
		act->connid = conn->connid;
		cc_user_send(user, ATMOP_P2P_CALL_ACTIVE, act, sizeof(*act));
		CCFREE(act);
	} else {
		struct atm_p2mp_call_active *act;

		user->config = USER_ROOT;
		act = CCZALLOC(sizeof(*act));
		if (act == NULL)
			return;
		act->connid = conn->connid;
		cc_user_send(user, ATMOP_P2MP_CALL_ACTIVE, act, sizeof(*act));
		CCFREE(act);
	}
}