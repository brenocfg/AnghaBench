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
struct ngsock {int refs; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * node; int /*<<< orphan*/  hmask; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/ * node_p ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_NETGRAPH_SOCK ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ngsock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ng_socket_free_priv(struct ngsock *priv)
{
	mtx_assert(&priv->mtx, MA_OWNED);

	priv->refs--;

	if (priv->refs == 0) {
		mtx_destroy(&priv->mtx);
		hashdestroy(priv->hash, M_NETGRAPH_SOCK, priv->hmask);
		free(priv, M_NETGRAPH_SOCK);
		return;
	}

	if ((priv->refs == 1) && (priv->node != NULL)) {
		node_p node = priv->node;

		priv->node = NULL;
		mtx_unlock(&priv->mtx);
		NG_NODE_UNREF(node);
		ng_rmnode_self(node);
	} else
		mtx_unlock(&priv->mtx);
}