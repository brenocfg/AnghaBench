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
struct uni_ie_epref {int /*<<< orphan*/  epref; } ;
struct ccparty {size_t state; } ;
struct ccconn {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 size_t CONN_SIG_PARTY_ADD_REJ_IND ; 
 size_t PARTY_ADD_WAIT_ACK ; 
 int /*<<< orphan*/  PARTY_WAIT_DESTROY ; 
 int /*<<< orphan*/  USER_SIG_ADD_PARTY_REJ ; 
 int /*<<< orphan*/ * cc_conn_sigtab ; 
 struct ccparty* cc_party_find (struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_party_log (struct ccparty*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cc_party_set_state (struct ccparty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_user_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptab ; 

__attribute__((used)) static void
cc_party_add_rej_ind(struct ccconn *conn, const struct uni_ie_epref *epref)
{
	struct ccparty *party;

	party = cc_party_find(conn, epref->epref);
	if (party == NULL) {
		cc_party_log(party, "no party for %s",
		    cc_conn_sigtab[CONN_SIG_PARTY_ADD_REJ_IND]);
		return;
	}
	if (party->state != PARTY_ADD_WAIT_ACK) {
		cc_party_log(party, "bad state=%s for signal=%s",
		    ptab[party->state],
		    cc_conn_sigtab[CONN_SIG_PARTY_ADD_REJ_IND]);
		return;
	}
	cc_party_set_state(party, PARTY_WAIT_DESTROY);
	cc_user_sig(conn->user, USER_SIG_ADD_PARTY_REJ, NULL, epref->epref);
}