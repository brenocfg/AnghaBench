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
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {int /*<<< orphan*/ ** hooks; TYPE_1__* links; } ;
struct TYPE_4__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/  const) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/  const) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ng_ppp_update (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
ng_ppp_disconnect(hook_p hook)
{
	const node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);
	const int index = (intptr_t)NG_HOOK_PRIVATE(hook);

	/* Zero out hook pointer */
	if (index < 0)
		priv->links[~index].hook = NULL;
	else
		priv->hooks[index] = NULL;

	/* Update derived info (or go away if no hooks left). */
	if (NG_NODE_NUMHOOKS(node) > 0)
		ng_ppp_update(node, 0);
	else if (NG_NODE_IS_VALID(node))
		ng_rmnode_self(node);

	return (0);
}