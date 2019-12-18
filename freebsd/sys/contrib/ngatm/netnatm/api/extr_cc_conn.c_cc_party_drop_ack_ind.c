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
struct TYPE_4__ {int /*<<< orphan*/  epref; } ;
struct uni_drop_party {int /*<<< orphan*/  cause; TYPE_1__ epref; } ;
struct TYPE_5__ {int /*<<< orphan*/  epref; } ;
struct ccparty {int state; TYPE_2__ epref; } ;
struct ccconn {TYPE_3__* user; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cause; } ;

/* Variables and functions */
 size_t CONN_SIG_DROP_PARTY_ACK_IND ; 
#define  PARTY_ACTIVE 132 
#define  PARTY_ADD_WAIT_ACK 131 
#define  PARTY_DROP_WAIT_ACK 130 
 int /*<<< orphan*/  PARTY_WAIT_DESTROY ; 
#define  PARTY_WAIT_SETUP_COMPL 129 
#define  PARTY_WAIT_SETUP_CONF 128 
 int /*<<< orphan*/  USER_SIG_ADD_PARTY_REJ ; 
 int /*<<< orphan*/  USER_SIG_DROP_PARTY_IND ; 
 int /*<<< orphan*/  USER_SIG_DROP_PARTY_OK ; 
 int /*<<< orphan*/ * cc_conn_sigtab ; 
 struct ccparty* cc_party_find (struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_party_log (struct ccparty*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cc_party_set_state (struct ccparty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_user_sig (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ptab ; 

__attribute__((used)) static void
cc_party_drop_ack_ind(struct ccconn *conn,
    const struct uni_drop_party *drop)
{
	struct ccparty *party;

	party = cc_party_find(conn, drop->epref.epref);
	if (party == NULL) {
		cc_party_log(party, "no party for %s",
		    cc_conn_sigtab[CONN_SIG_DROP_PARTY_ACK_IND]);
		return;
	}
	switch (party->state) {

	  case PARTY_ACTIVE:			/* P1 */
		memset(&conn->user->cause[1], 0, sizeof(conn->user->cause[1]));
		conn->user->cause[0] = drop->cause;
		cc_party_set_state(party, PARTY_WAIT_DESTROY);
		cc_user_sig(conn->user, USER_SIG_DROP_PARTY_IND,
		    NULL, party->epref.epref);
		break;

	  case PARTY_ADD_WAIT_ACK:		/* P4 */
		memset(&conn->user->cause[1], 0, sizeof(conn->user->cause[1]));
		conn->user->cause[0] = drop->cause;
		cc_party_set_state(party, PARTY_WAIT_DESTROY);
		cc_user_sig(conn->user, USER_SIG_ADD_PARTY_REJ,
		    NULL, party->epref.epref);
		break;

	  case PARTY_DROP_WAIT_ACK:		/* P6 */
		cc_party_set_state(party, PARTY_WAIT_DESTROY);
		cc_user_sig(conn->user, USER_SIG_DROP_PARTY_OK, NULL, 0);
		break;

	  case PARTY_WAIT_SETUP_COMPL:		/* P8 */
	  case PARTY_WAIT_SETUP_CONF:		/* P10 */
		cc_party_set_state(party, PARTY_WAIT_DESTROY);
		break;

	  default:
		cc_party_log(party, "bad state=%s for signal=%s",
		    ptab[party->state],
		    cc_conn_sigtab[CONN_SIG_DROP_PARTY_ACK_IND]);
		break;
	}
}