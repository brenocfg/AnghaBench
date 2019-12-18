#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/  const) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Pred1Init (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
ng_pred1_disconnect(hook_p hook)
{
	const node_p node = NG_HOOK_NODE(hook);

	Pred1Init(node);

	/* Go away if no longer connected. */
	if ((NG_NODE_NUMHOOKS(node) == 0) && NG_NODE_IS_VALID(node))
		ng_rmnode_self(node);
	return (0);
}