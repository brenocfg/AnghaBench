#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ng_hci_unit_con_p ;
struct TYPE_8__ {scalar_t__ link_type; int /*<<< orphan*/  conq; int /*<<< orphan*/  pending; TYPE_1__* unit; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_HCI ; 
 int /*<<< orphan*/  NG_BT_ITEMQ_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_ACL_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_SCO_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NG_HCI_LINK_SCO ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

void
ng_hci_free_con(ng_hci_unit_con_p con)
{ 
	LIST_REMOVE(con, next);

	/*
	 * If we have pending packets then assume that Host Controller has 
	 * flushed these packets and we can free them too
	 */

	if (con->link_type != NG_HCI_LINK_SCO)
		NG_HCI_BUFF_ACL_FREE(con->unit->buffer, con->pending);
	else
		NG_HCI_BUFF_SCO_FREE(con->unit->buffer, con->pending);

	NG_BT_ITEMQ_DESTROY(&con->conq);

	bzero(con, sizeof(*con));
	free(con, M_NETGRAPH_HCI);
}