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
typedef  TYPE_1__* ng_l2cap_p ;
typedef  scalar_t__ hook_p ;
struct TYPE_4__ {scalar_t__ hci; scalar_t__ l2c; scalar_t__ ctl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_l2cap_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_l2cap_destroy_channels (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_l2cap_disconnect(hook_p hook)
{
	ng_l2cap_p	 l2cap = (ng_l2cap_p) NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	hook_p		*h = NULL;

	if (hook == l2cap->hci) {
		ng_l2cap_cleanup(l2cap);
		h = &l2cap->hci;
	} else
	if (hook == l2cap->l2c) {
		ng_l2cap_destroy_channels(l2cap);
		h = &l2cap->l2c;
	} else
	if (hook == l2cap->ctl)
		h = &l2cap->ctl;
	else
		return (EINVAL);

	*h = NULL;

	/* Shutdown when all hooks are disconnected */
	if (NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0 &&
	    NG_NODE_IS_VALID(NG_HOOK_NODE(hook)))
		ng_rmnode_self(NG_HOOK_NODE(hook));

	return (0);
}