#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ng_mesg {int dummy; } ;
typedef  TYPE_1__* priv_p ;
typedef  scalar_t__ hook_p ;
struct TYPE_3__ {scalar_t__ ethernet_hook; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_ETHER_COOKIE ; 
 int /*<<< orphan*/  NGM_ETHER_GET_ENADDR ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_ID (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_PEER_NODE (scalar_t__) ; 
 int /*<<< orphan*/  NG_SEND_MSG_ID (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_pppoe_connect(hook_p hook)
{
	const priv_p privp = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct ng_mesg *msg;
	int error;

	if (hook != privp->ethernet_hook)
		return (0);

	/*
	 * If this is Ethernet hook, then request MAC address
	 * from our downstream.
	 */
	NG_MKMESSAGE(msg, NGM_ETHER_COOKIE, NGM_ETHER_GET_ENADDR, 0, M_NOWAIT);
	if (msg == NULL)
		return (ENOBUFS);

	/*
	 * Our hook and peer hook have HK_INVALID flag set,
	 * so we can't use NG_SEND_MSG_HOOK() macro here.
	 */
	NG_SEND_MSG_ID(error, privp->node, msg,
	    NG_NODE_ID(NG_PEER_NODE(privp->ethernet_hook)),
	    NG_NODE_ID(privp->node));

	return (error);
}