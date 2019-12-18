#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_3__* hpriv_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_11__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_9__ {int /*<<< orphan*/ * hook; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lower; TYPE_1__ uppersess; int /*<<< orphan*/ * upper; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 TYPE_3__* NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/  const) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/  const) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  free (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_pptpgre_reset (TYPE_3__* const) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sessions ; 

__attribute__((used)) static int
ng_pptpgre_disconnect(hook_p hook)
{
	const node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);
	const hpriv_p hpriv = NG_HOOK_PRIVATE(hook);

	/* Zero out hook pointer */
	if (hook == priv->upper) {
		priv->upper = NULL;
		priv->uppersess.hook = NULL;
	} else if (hook == priv->lower) {
		priv->lower = NULL;
	} else {
		/* Reset node (stops timers) */
		ng_pptpgre_reset(hpriv);

		LIST_REMOVE(hpriv, sessions);
		mtx_destroy(&hpriv->mtx);
		free(hpriv, M_NETGRAPH);
	}

	/* Go away if no longer connected to anything */
	if ((NG_NODE_NUMHOOKS(node) == 0)
	&& (NG_NODE_IS_VALID(node)))
		ng_rmnode_self(node);
	return (0);
}