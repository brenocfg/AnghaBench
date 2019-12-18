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
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngh_disconnect(hook_p hook)
{

	free(NG_HOOK_PRIVATE(hook), M_NETGRAPH);
	NG_HOOK_SET_PRIVATE(hook, NULL);
	if (NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0)
		ng_rmnode_self(NG_HOOK_NODE(hook));
	return (0);
}