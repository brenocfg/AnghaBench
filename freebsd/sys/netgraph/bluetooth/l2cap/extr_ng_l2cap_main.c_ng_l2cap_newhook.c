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
typedef  TYPE_1__* ng_l2cap_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_2__ {int /*<<< orphan*/ * ctl; int /*<<< orphan*/ * l2c; int /*<<< orphan*/ * hci; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_L2CAP_HOOK_CTL ; 
 int /*<<< orphan*/  NG_L2CAP_HOOK_HCI ; 
 int /*<<< orphan*/  NG_L2CAP_HOOK_L2C ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_l2cap_newhook(node_p node, hook_p hook, char const *name)
{
	ng_l2cap_p	 l2cap = (ng_l2cap_p) NG_NODE_PRIVATE(node);
	hook_p		*h = NULL;

	if (strcmp(name, NG_L2CAP_HOOK_HCI) == 0)
		h = &l2cap->hci;
	else if (strcmp(name, NG_L2CAP_HOOK_L2C) == 0)
		h = &l2cap->l2c;
	else if (strcmp(name, NG_L2CAP_HOOK_CTL) == 0)
		h = &l2cap->ctl;
	else
		return (EINVAL);

	if (*h != NULL)
		return (EISCONN);

	*h = hook;

	return (0);
}