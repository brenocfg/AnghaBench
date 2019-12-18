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
struct TYPE_5__ {int /*<<< orphan*/  failAlg; int /*<<< orphan*/  xmitAlg; } ;
struct TYPE_6__ {int /*<<< orphan*/  node; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NG_ONE2MANY_FAIL_MANUAL ; 
 int /*<<< orphan*/  NG_ONE2MANY_XMIT_ROUNDROBIN ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_one2many_constructor(node_p node)
{
	priv_p priv;

	/* Allocate and initialize private info */
	priv = malloc(sizeof(*priv), M_NETGRAPH, M_WAITOK | M_ZERO);
	priv->conf.xmitAlg = NG_ONE2MANY_XMIT_ROUNDROBIN;
	priv->conf.failAlg = NG_ONE2MANY_FAIL_MANUAL;

	/* cross reference */
	NG_NODE_SET_PRIVATE(node, priv);
	priv->node = node;

	/* Done */
	return (0);
}