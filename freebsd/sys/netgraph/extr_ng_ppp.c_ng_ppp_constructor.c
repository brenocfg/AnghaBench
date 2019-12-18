#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_6__ {int /*<<< orphan*/  xmtx; int /*<<< orphan*/  rmtx; int /*<<< orphan*/  fragTimer; TYPE_1__* links; int /*<<< orphan*/ * fragsmem; int /*<<< orphan*/  fragsfree; int /*<<< orphan*/  frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int MP_MAX_QUEUE_LEN ; 
 int /*<<< orphan*/  MP_NOSEQ ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NETGRAPH_PPP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int NG_PPP_MAX_LINKS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_qent ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_ppp_constructor(node_p node)
{
	priv_p priv;
	int i;

	/* Allocate private structure */
	priv = malloc(sizeof(*priv), M_NETGRAPH_PPP, M_WAITOK | M_ZERO);

	NG_NODE_SET_PRIVATE(node, priv);

	/* Initialize state */
	TAILQ_INIT(&priv->frags);
	TAILQ_INIT(&priv->fragsfree);
	for (i = 0; i < MP_MAX_QUEUE_LEN; i++)
		TAILQ_INSERT_TAIL(&priv->fragsfree, &priv->fragsmem[i], f_qent);
	for (i = 0; i < NG_PPP_MAX_LINKS; i++)
		priv->links[i].seq = MP_NOSEQ;
	ng_callout_init(&priv->fragTimer);

	mtx_init(&priv->rmtx, "ng_ppp_recv", NULL, MTX_DEF);
	mtx_init(&priv->xmtx, "ng_ppp_xmit", NULL, MTX_DEF);

	/* Done */
	return (0);
}