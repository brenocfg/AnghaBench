#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  TYPE_1__* priv_p ;
typedef  scalar_t__ node_p ;
typedef  TYPE_2__* link_p ;
typedef  int /*<<< orphan*/  linkName ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_7__ {int /*<<< orphan*/  hook; } ;
struct TYPE_6__ {int /*<<< orphan*/  numLinks; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELOOP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NETGRAPH_BRIDGE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 char* NG_BRIDGE_HOOK_LINK_PREFIX ; 
 int NG_HOOKSIZ ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* NG_NODE_PRIVATE (scalar_t__) ; 
 scalar_t__ NG_PEER_NODE (int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static	int
ng_bridge_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	/* Check for a link hook */
	if (strlen(name) > strlen(NG_BRIDGE_HOOK_LINK_PREFIX)) {
		char linkName[NG_HOOKSIZ];
		u_int32_t linkNum;
		link_p link;

		/* primitive parsing */
		linkNum = strtoul(name + strlen(NG_BRIDGE_HOOK_LINK_PREFIX),
				  NULL, 10);
		/* validation by comparing against the reconstucted name  */
		snprintf(linkName, sizeof(linkName),
			 "%s%u", NG_BRIDGE_HOOK_LINK_PREFIX,
			 linkNum);
		if (strcmp(linkName, name) != 0)
			return (EINVAL);
		
		if(NG_PEER_NODE(hook) == node)
		        return (ELOOP);

		link = malloc(sizeof(*link), M_NETGRAPH_BRIDGE,
			      M_WAITOK|M_ZERO);
		if (link == NULL)
			return (ENOMEM);
		link->hook = hook;
		NG_HOOK_SET_PRIVATE(hook, link);
		priv->numLinks++;
		return (0);
	}

	/* Unknown hook name */
	return (EINVAL);
}