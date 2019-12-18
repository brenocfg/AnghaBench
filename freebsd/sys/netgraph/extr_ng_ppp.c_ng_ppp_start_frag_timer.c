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
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_3__ {int /*<<< orphan*/  fragTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FRAGTIMER_INTERVAL ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_ppp_frag_timeout ; 

__attribute__((used)) static void
ng_ppp_start_frag_timer(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (!(callout_pending(&priv->fragTimer)))
		ng_callout(&priv->fragTimer, node, NULL, MP_FRAGTIMER_INTERVAL,
		    ng_ppp_frag_timeout, NULL, 0);
}