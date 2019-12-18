#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ccparty {int state; TYPE_2__* conn; } ;
typedef  enum party_state { ____Placeholder_party_state } party_state ;
struct TYPE_4__ {TYPE_1__* cc; } ;
struct TYPE_3__ {int log; } ;

/* Variables and functions */
 int CCLOG_PARTY_STATE ; 
 int /*<<< orphan*/  cc_party_log (struct ccparty*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptab ; 

void
cc_party_set_state(struct ccparty *party, enum party_state ns)
{

	if (party->state != ns) {
		if (party->conn->cc->log & CCLOG_PARTY_STATE)
			cc_party_log(party, "%s -> %s",
			    ptab[party->state], ptab[ns]);
		party->state = ns;
	}
}