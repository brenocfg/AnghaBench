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
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_6__ {int peer_win; int /*<<< orphan*/  rexmit_max_to; int /*<<< orphan*/  rexmit_max; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sesshash; TYPE_1__ conf; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2TP_MAX_REXMIT ; 
 int /*<<< orphan*/  L2TP_MAX_REXMIT_TO ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_NETGRAPH_L2TP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int SESSHASHSIZE ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ng_l2tp_seq_init (TYPE_2__*) ; 

__attribute__((used)) static int
ng_l2tp_constructor(node_p node)
{
	priv_p priv;
	int	i;

	/* Allocate private structure */
	priv = malloc(sizeof(*priv), M_NETGRAPH_L2TP, M_WAITOK | M_ZERO);
	NG_NODE_SET_PRIVATE(node, priv);
	priv->node = node;

	/* Apply a semi-reasonable default configuration */
	priv->conf.peer_win = 1;
	priv->conf.rexmit_max = L2TP_MAX_REXMIT;
	priv->conf.rexmit_max_to = L2TP_MAX_REXMIT_TO;

	/* Initialize sequence number state */
	ng_l2tp_seq_init(priv);

	for (i = 0; i < SESSHASHSIZE; i++)
	    LIST_INIT(&priv->sesshash[i]);

	/* Done */
	return (0);
}