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
struct ifnet {int /*<<< orphan*/  if_vnet; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int /*<<< orphan*/  link_status; int /*<<< orphan*/ * ether; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int EISCONN ; 
 int EPFNOSUPPORT ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  NG_EIFACE_HOOK_ETHER ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  NG_HOOK_SET_TO_INBOUND (int /*<<< orphan*/ *) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_eiface_newhook(node_p node, hook_p hook, const char *name)
{
	priv_p priv = NG_NODE_PRIVATE(node);
	struct ifnet *ifp = priv->ifp;

	if (strcmp(name, NG_EIFACE_HOOK_ETHER))
		return (EPFNOSUPPORT);
	if (priv->ether != NULL)
		return (EISCONN);
	priv->ether = hook;
	NG_HOOK_SET_PRIVATE(hook, &priv->ether);
	NG_HOOK_SET_TO_INBOUND(hook);

	priv->link_status |= IFM_ACTIVE;
	CURVNET_SET_QUIET(ifp->if_vnet);
	if_link_state_change(ifp, LINK_STATE_UP);
	CURVNET_RESTORE();

	return (0);
}