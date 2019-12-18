#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id_num; } ;
struct TYPE_6__ {int answer; int /*<<< orphan*/  id_num; } ;
typedef  TYPE_1__ CTL_RESPONSE ;

/* Variables and functions */
 int /*<<< orphan*/  LOOK_UP ; 
#define  SUCCESS 128 
 int /*<<< orphan*/  ctl_transact (int /*<<< orphan*/ ,TYPE_2__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* current_state ; 
 int /*<<< orphan*/  his_machine_addr ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_2__ msg ; 

int
look_for_invite(CTL_RESPONSE *rp)
{
	current_state = "Checking for invitation on caller's machine";
	ctl_transact(his_machine_addr, msg, LOOK_UP, rp);
	/* the switch is for later options, such as multiple invitations */
	switch (rp->answer) {

	case SUCCESS:
		msg.id_num = htonl(rp->id_num);
		return (1);

	default:
		/* there wasn't an invitation waiting for us */
		return (0);
	}
}