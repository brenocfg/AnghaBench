#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_3__* link_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_8__ {scalar_t__ loopCount; } ;
struct TYPE_6__ {int debugLevel; } ;
struct TYPE_7__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  NG_HOOK_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_3__* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_bridge_nodename (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_bridge_unmute(hook_p hook, void *arg)
{
	link_p link = NG_HOOK_PRIVATE(hook);
	node_p node = NG_HOOK_NODE(hook);
	priv_p priv = NG_NODE_PRIVATE(node);
	int *counter = arg;

	if (link->loopCount != 0) {
		link->loopCount--;
		if (link->loopCount == 0 && priv->conf.debugLevel >= 2) {
			log(LOG_INFO, "ng_bridge: %s:"
			    " restoring looped back %s\n",
			    ng_bridge_nodename(node), NG_HOOK_NAME(hook));
		}
	}
	(*counter)++;
	return (1);
}