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
struct ccparty {size_t state; } ;
struct TYPE_2__ {int /*<<< orphan*/  epref; } ;
struct ccconn {TYPE_1__ epref; } ;

/* Variables and functions */
 size_t CONN_SIG_SETUP_CONFIRM ; 
 int /*<<< orphan*/  PARTY_ACTIVE ; 
 size_t PARTY_WAIT_SETUP_CONF ; 
 int /*<<< orphan*/ * cc_conn_sigtab ; 
 struct ccparty* cc_party_find (struct ccconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_party_log (struct ccparty*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cc_party_set_state (struct ccparty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptab ; 

__attribute__((used)) static void
cc_party_setup_conf(struct ccconn *conn)
{
	struct ccparty *party;

	party = cc_party_find(conn, conn->epref.epref);
	if (party == NULL) {
		cc_party_log(party, "no party for %s",
		    cc_conn_sigtab[CONN_SIG_SETUP_CONFIRM]);
		return;
	}
	if (party->state != PARTY_WAIT_SETUP_CONF) {
		cc_party_log(party, "bad state=%s for signal=%s",
		    ptab[party->state], cc_conn_sigtab[CONN_SIG_SETUP_CONFIRM]);
		return;
	}
	cc_party_set_state(party, PARTY_ACTIVE);
}