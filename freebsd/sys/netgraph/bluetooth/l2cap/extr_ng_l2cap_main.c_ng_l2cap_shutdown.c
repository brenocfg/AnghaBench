#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_1__* ng_l2cap_p ;
struct TYPE_5__ {int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_L2CAP ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_l2cap_cleanup (TYPE_1__*) ; 

__attribute__((used)) static int
ng_l2cap_shutdown(node_p node)
{
	ng_l2cap_p	l2cap = (ng_l2cap_p) NG_NODE_PRIVATE(node);

	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);

	/* Clean up L2CAP node. Delete all connection, channels and commands */
	l2cap->node = NULL;
	ng_l2cap_cleanup(l2cap);

	bzero(l2cap, sizeof(*l2cap));
	free(l2cap, M_NETGRAPH_L2CAP);

	return (0);
}