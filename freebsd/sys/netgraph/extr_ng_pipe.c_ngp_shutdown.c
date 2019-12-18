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
typedef  TYPE_3__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_7__ {int /*<<< orphan*/ * hook; } ;
struct TYPE_6__ {int /*<<< orphan*/ * hook; } ;
struct TYPE_8__ {TYPE_2__ lower; TYPE_1__ upper; int /*<<< orphan*/  timer; scalar_t__ timer_scheduled; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NG_PIPE ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_bypass (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmhook_self (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_uncallout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngp_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (priv->timer_scheduled)
		ng_uncallout(&priv->timer, node);
	if (priv->lower.hook && priv->upper.hook)
		ng_bypass(priv->lower.hook, priv->upper.hook);
	else {
		if (priv->upper.hook != NULL)
			ng_rmhook_self(priv->upper.hook);
		if (priv->lower.hook != NULL)
			ng_rmhook_self(priv->lower.hook);
	}
	NG_NODE_UNREF(node);
	free(priv, M_NG_PIPE);
	return (0);
}