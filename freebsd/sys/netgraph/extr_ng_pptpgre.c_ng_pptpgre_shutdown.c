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
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_7__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_6__ {TYPE_2__ uppersess; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_pptpgre_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  sessions ; 

__attribute__((used)) static int
ng_pptpgre_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	/* Reset node (stops timers) */
	ng_pptpgre_reset(&priv->uppersess);

	LIST_REMOVE(&priv->uppersess, sessions);
	mtx_destroy(&priv->uppersess.mtx);

	free(priv, M_NETGRAPH);

	/* Decrement ref count */
	NG_NODE_UNREF(node);
	return (0);
}