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
typedef  TYPE_1__* ng_hci_unit_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int state; int /*<<< orphan*/ * drv; int /*<<< orphan*/ * raw; int /*<<< orphan*/ * sco; int /*<<< orphan*/ * acl; } ;

/* Variables and functions */
 int EINVAL ; 
 int NG_HCI_UNIT_CONNECTED ; 
 int NG_HCI_UNIT_INITED ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_hci_unit_clean (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_hci_disconnect(hook_p hook)
{
	ng_hci_unit_p	 unit = (ng_hci_unit_p) NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	if (hook == unit->acl)
		unit->acl = NULL;
	else if (hook == unit->sco)
		unit->sco = NULL;
	else if (hook == unit->raw)
		unit->raw = NULL;
	else if (hook == unit->drv) {
		unit->drv = NULL;

		/* Connection terminated by local host */
		ng_hci_unit_clean(unit, 0x16);
		unit->state &= ~(NG_HCI_UNIT_CONNECTED|NG_HCI_UNIT_INITED);
	} else
		return (EINVAL);

	/* Shutdown when all hooks are disconnected */
	if ((NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0) &&
	    (NG_NODE_IS_VALID(NG_HOOK_NODE(hook))))
		ng_rmnode_self(NG_HOOK_NODE(hook));

	return (0);
}