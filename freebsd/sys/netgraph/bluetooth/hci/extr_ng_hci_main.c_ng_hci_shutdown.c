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
typedef  TYPE_1__* ng_hci_unit_p ;
struct TYPE_5__ {int /*<<< orphan*/  cmdq; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_HCI ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_hci_unit_clean (TYPE_1__*,int) ; 

__attribute__((used)) static int
ng_hci_shutdown(node_p node)
{
	ng_hci_unit_p	unit = (ng_hci_unit_p) NG_NODE_PRIVATE(node);

	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);

	unit->node = NULL;
	ng_hci_unit_clean(unit, 0x16 /* Connection terminated by local host */);

	NG_BT_MBUFQ_DESTROY(&unit->cmdq);

	bzero(unit, sizeof(*unit));
	free(unit, M_NETGRAPH_HCI);

	return (0);
}