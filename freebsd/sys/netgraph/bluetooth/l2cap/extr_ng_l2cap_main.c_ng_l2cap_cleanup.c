#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ng_l2cap_p ;
typedef  TYPE_2__* ng_l2cap_con_p ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  con_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int NG_L2CAP_CON_AUTO_DISCON_TIMO ; 
 int NG_L2CAP_CON_LP_TIMO ; 
 int /*<<< orphan*/  ng_l2cap_con_fail (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ng_l2cap_discon_untimeout (TYPE_2__*) ; 
 int /*<<< orphan*/  ng_l2cap_lp_untimeout (TYPE_2__*) ; 

__attribute__((used)) static void
ng_l2cap_cleanup(ng_l2cap_p l2cap)
{
	ng_l2cap_con_p	con = NULL;

	/* Clean up connection and channels */
	while (!LIST_EMPTY(&l2cap->con_list)) {
		con = LIST_FIRST(&l2cap->con_list);

		if (con->flags & NG_L2CAP_CON_LP_TIMO)
			ng_l2cap_lp_untimeout(con);
		else if (con->flags & NG_L2CAP_CON_AUTO_DISCON_TIMO)
			ng_l2cap_discon_untimeout(con);

		/* Connection terminated by local host */
		ng_l2cap_con_fail(con, 0x16);
	}
}