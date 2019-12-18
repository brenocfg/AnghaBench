#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ng_hci_unit_p ;
typedef  TYPE_2__* ng_hci_unit_con_p ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {int state; int /*<<< orphan*/  buffer; int /*<<< orphan*/  con_list; int /*<<< orphan*/  cmdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_DRAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_ACL_FREE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_ACL_TOTAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_CMD_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_SCO_FREE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_SCO_TOTAL (int /*<<< orphan*/ ,int) ; 
 int NG_HCI_CON_TIMEOUT_PENDING ; 
 int NG_HCI_UNIT_COMMAND_PENDING ; 
 int /*<<< orphan*/  ng_hci_command_untimeout (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_hci_con_untimeout (TYPE_2__*) ; 
 int /*<<< orphan*/  ng_hci_flush_neighbor_cache (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_hci_free_con (TYPE_2__*) ; 
 int /*<<< orphan*/  ng_hci_lp_discon_ind (TYPE_2__*,int) ; 

void
ng_hci_unit_clean(ng_hci_unit_p unit, int reason)
{
	int	size;

	/* Drain command queue */
	if (unit->state & NG_HCI_UNIT_COMMAND_PENDING)
		ng_hci_command_untimeout(unit);

	NG_BT_MBUFQ_DRAIN(&unit->cmdq);
	NG_HCI_BUFF_CMD_SET(unit->buffer, 1);

	/* Clean up connection list */
	while (!LIST_EMPTY(&unit->con_list)) {
		ng_hci_unit_con_p	con = LIST_FIRST(&unit->con_list);

		/* Remove all timeouts (if any) */
		if (con->flags & NG_HCI_CON_TIMEOUT_PENDING)
			ng_hci_con_untimeout(con);

		/*
		 * Notify upper layer protocol and destroy connection 
		 * descriptor. Do not really care about the result.
		 */

		ng_hci_lp_discon_ind(con, reason);
		ng_hci_free_con(con);
	}

	NG_HCI_BUFF_ACL_TOTAL(unit->buffer, size);
	NG_HCI_BUFF_ACL_FREE(unit->buffer, size);

	NG_HCI_BUFF_SCO_TOTAL(unit->buffer, size);
	NG_HCI_BUFF_SCO_FREE(unit->buffer, size);

	/* Clean up neighbors list */
	ng_hci_flush_neighbor_cache(unit);
}