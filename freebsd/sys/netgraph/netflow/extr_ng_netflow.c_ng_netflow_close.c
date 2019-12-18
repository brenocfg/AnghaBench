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
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_4__ {int /*<<< orphan*/  exp_callout; } ;

/* Variables and functions */
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_netflow_cache_flush (TYPE_1__* const) ; 

__attribute__((used)) static int
ng_netflow_close(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	callout_drain(&priv->exp_callout);
	ng_netflow_cache_flush(priv);

	return (0);
}