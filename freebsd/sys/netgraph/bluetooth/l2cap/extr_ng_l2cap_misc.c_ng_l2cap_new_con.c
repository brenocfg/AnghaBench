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
typedef  TYPE_1__* ng_l2cap_p ;
typedef  TYPE_2__* ng_l2cap_con_p ;
typedef  int /*<<< orphan*/  bdaddr_p ;
struct TYPE_8__ {int linktype; int /*<<< orphan*/  cmd_list; scalar_t__ ident; int /*<<< orphan*/  con_timo; int /*<<< orphan*/  remote; int /*<<< orphan*/  con_handle; scalar_t__ encryption; int /*<<< orphan*/  state; TYPE_1__* l2cap; } ;
struct TYPE_7__ {int /*<<< orphan*/  con_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_L2CAP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_L2CAP_CON_CLOSED ; 
 scalar_t__ NG_L2CAP_FIRST_IDENT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 

ng_l2cap_con_p
ng_l2cap_new_con(ng_l2cap_p l2cap, bdaddr_p bdaddr, int type)
{
	static int	fake_con_handle = 0x0f00;
	ng_l2cap_con_p	con = NULL;

	/* Create new connection descriptor */
	con = malloc(sizeof(*con), M_NETGRAPH_L2CAP,
		M_NOWAIT|M_ZERO);
	if (con == NULL)
		return (NULL);

	con->l2cap = l2cap;
	con->state = NG_L2CAP_CON_CLOSED;
	con->encryption = 0;
	/*
	 * XXX
	 *
	 * Assign fake connection handle to the connection descriptor.
	 * Bluetooth specification marks 0x0f00 - 0x0fff connection 
	 * handles as reserved. We need this fake connection handles 
	 * for timeouts. Connection handle will be passed as argument
	 * to timeout so when timeout happens we can find the right
	 * connection descriptor. We can not pass pointers, because
	 * timeouts are external (to Netgraph) events and there might
	 * be a race when node/hook goes down and timeout event already
	 * went into node's queue
	 */

	con->con_handle = fake_con_handle ++;
	if (fake_con_handle > 0x0fff)
		fake_con_handle = 0x0f00;

	bcopy(bdaddr, &con->remote, sizeof(con->remote));
	con->linktype = type;
	ng_callout_init(&con->con_timo);

	con->ident = NG_L2CAP_FIRST_IDENT - 1;
	TAILQ_INIT(&con->cmd_list);

	/* Link connection */
	LIST_INSERT_HEAD(&l2cap->con_list, con, next); 

	return (con);
}