#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
typedef  TYPE_1__* ng_l2cap_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  scalar_t__ hook_p ;
struct TYPE_4__ {scalar_t__ hci; scalar_t__ l2c; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int ng_l2cap_l2ca_write_req (TYPE_1__*,struct mbuf*) ; 
 int ng_l2cap_lp_receive (TYPE_1__*,struct mbuf*) ; 

__attribute__((used)) static int
ng_l2cap_rcvdata(hook_p hook, item_p item)
{
	ng_l2cap_p	 l2cap = (ng_l2cap_p) NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct mbuf	*m = NULL;
	int		 error = 0;

	/* Detach mbuf, discard item and process data */
	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	if (hook == l2cap->hci)
		error = ng_l2cap_lp_receive(l2cap, m);
	else if (hook == l2cap->l2c)
		error = ng_l2cap_l2ca_write_req(l2cap, m);
	else {
		NG_FREE_M(m);
		error = EINVAL;
	}

	return (error);
}