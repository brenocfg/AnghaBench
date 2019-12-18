#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_6__ {int /*<<< orphan*/  reorderTimer; scalar_t__ roq_len; int /*<<< orphan*/  roq; int /*<<< orphan*/  node; int /*<<< orphan*/  rackTimer; int /*<<< orphan*/  sackTimer; int /*<<< orphan*/  mtx; } ;
struct TYPE_5__ {TYPE_4__ uppersess; int /*<<< orphan*/ * sesshash; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SESSHASHSIZE ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sessions ; 

__attribute__((used)) static int
ng_pptpgre_constructor(node_p node)
{
	priv_p priv;
	int i;

	/* Allocate private structure */
	priv = malloc(sizeof(*priv), M_NETGRAPH, M_WAITOK | M_ZERO);

	NG_NODE_SET_PRIVATE(node, priv);

	/* Initialize state */
	mtx_init(&priv->uppersess.mtx, "ng_pptp", NULL, MTX_DEF);
	ng_callout_init(&priv->uppersess.sackTimer);
	ng_callout_init(&priv->uppersess.rackTimer);
	priv->uppersess.node = node;

	SLIST_INIT(&priv->uppersess.roq);
	priv->uppersess.roq_len = 0;
	ng_callout_init(&priv->uppersess.reorderTimer);

	for (i = 0; i < SESSHASHSIZE; i++)
	    LIST_INIT(&priv->sesshash[i]);

	LIST_INSERT_HEAD(&priv->sesshash[0], &priv->uppersess, sessions);

	/* Done */
	return (0);
}