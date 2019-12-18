#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_10__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  node; int /*<<< orphan*/  embryos; TYPE_2__* so; } ;

/* Variables and functions */
 int KSF_EMBRYONIC ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_KSOCKET ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  SO_SND ; 
 int /*<<< orphan*/  bzero (TYPE_1__* const,int) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siblings ; 
 int /*<<< orphan*/  soclose (TYPE_2__*) ; 
 int /*<<< orphan*/  soupcall_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ksocket_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	priv_p embryo;

	/* Close our socket (if any) */
	if (priv->so != NULL) {
		SOCKBUF_LOCK(&priv->so->so_rcv);
		soupcall_clear(priv->so, SO_RCV);
		SOCKBUF_UNLOCK(&priv->so->so_rcv);
		SOCKBUF_LOCK(&priv->so->so_snd);
		soupcall_clear(priv->so, SO_SND);
		SOCKBUF_UNLOCK(&priv->so->so_snd);
		soclose(priv->so);
		priv->so = NULL;
	}

	/* If we are an embryo, take ourselves out of the parent's list */
	if (priv->flags & KSF_EMBRYONIC) {
		LIST_REMOVE(priv, siblings);
		priv->flags &= ~KSF_EMBRYONIC;
	}

	/* Remove any embryonic children we have */
	while (!LIST_EMPTY(&priv->embryos)) {
		embryo = LIST_FIRST(&priv->embryos);
		ng_rmnode_self(embryo->node);
	}

	/* Take down netgraph node */
	bzero(priv, sizeof(*priv));
	free(priv, M_NETGRAPH_KSOCKET);
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);		/* let the node escape */
	return (0);
}