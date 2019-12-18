#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {int /*<<< orphan*/  if_vnet; } ;
struct TYPE_4__ {TYPE_2__* ifp; int /*<<< orphan*/  link_status; int /*<<< orphan*/ * ether; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_eiface_disconnect(hook_p hook)
{
	const priv_p priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	priv->ether = NULL;
	priv->link_status &= ~IFM_ACTIVE;
	CURVNET_SET_QUIET(priv->ifp->if_vnet);
	if_link_state_change(priv->ifp, LINK_STATE_DOWN);
	CURVNET_RESTORE();
	return (0);
}