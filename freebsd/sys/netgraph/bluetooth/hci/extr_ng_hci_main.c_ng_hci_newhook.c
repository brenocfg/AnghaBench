#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_1__* ng_hci_unit_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_2__ {int /*<<< orphan*/ * raw; int /*<<< orphan*/ * sco; int /*<<< orphan*/ * acl; int /*<<< orphan*/ * drv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_HCI_HOOK_ACL ; 
 int /*<<< orphan*/  NG_HCI_HOOK_DRV ; 
 int /*<<< orphan*/  NG_HCI_HOOK_RAW ; 
 int /*<<< orphan*/  NG_HCI_HOOK_SCO ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_hci_newhook(node_p node, hook_p hook, char const *name)
{
	ng_hci_unit_p	 unit = (ng_hci_unit_p) NG_NODE_PRIVATE(node);
	hook_p		*h = NULL;

	if (strcmp(name, NG_HCI_HOOK_DRV) == 0)
		h = &unit->drv;
	else if (strcmp(name, NG_HCI_HOOK_ACL) == 0)
		h = &unit->acl;
	else if (strcmp(name, NG_HCI_HOOK_SCO) == 0)
		h = &unit->sco;
	else if (strcmp(name, NG_HCI_HOOK_RAW) == 0)
		h = &unit->raw;
	else
		return (EINVAL);

	if (*h != NULL)
		return (EISCONN);

	*h = hook;

	return (0);
}