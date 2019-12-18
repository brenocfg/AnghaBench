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
struct ngsock {int /*<<< orphan*/ * node; struct ngpcb* ctlsock; struct ngpcb* datasock; int /*<<< orphan*/  mtx; } ;
struct ngpcb {int /*<<< orphan*/  ng_socket; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 struct ngsock* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_socket_free_priv (struct ngsock* const) ; 
 int /*<<< orphan*/  soisdisconnected (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngs_shutdown(node_p node)
{
	struct ngsock *const priv = NG_NODE_PRIVATE(node);
	struct ngpcb *dpcbp, *pcbp;

	mtx_lock(&priv->mtx);
	dpcbp = priv->datasock;
	pcbp = priv->ctlsock;

	if (dpcbp != NULL)
		soisdisconnected(dpcbp->ng_socket);

	if (pcbp != NULL)
		soisdisconnected(pcbp->ng_socket);

	priv->node = NULL;
	NG_NODE_SET_PRIVATE(node, NULL);
	ng_socket_free_priv(priv);

	NG_NODE_UNREF(node);
	return (0);
}