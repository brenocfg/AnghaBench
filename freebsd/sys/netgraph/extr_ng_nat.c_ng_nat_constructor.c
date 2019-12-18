#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_4__ {int nextid; int /*<<< orphan*/  node; int /*<<< orphan*/  redirhead; int /*<<< orphan*/  dlt; scalar_t__ rdrcount; int /*<<< orphan*/  lib; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_RAW ; 
 int /*<<< orphan*/  LibAliasInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LibAliasSetMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_FORCE_WRITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PKT_ALIAS_SAME_PORTS ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_nat_constructor(node_p node)
{
	priv_p priv;

	/* Initialize private descriptor. */
	priv = malloc(sizeof(*priv), M_NETGRAPH, M_WAITOK | M_ZERO);

	/* Init aliasing engine. */
	priv->lib = LibAliasInit(NULL);

	/* Set same ports on. */
	(void )LibAliasSetMode(priv->lib, PKT_ALIAS_SAME_PORTS,
	    PKT_ALIAS_SAME_PORTS);

	/* Init redirects housekeeping. */
	priv->rdrcount = 0;
	priv->nextid = 1;
	priv->dlt = DLT_RAW;
	STAILQ_INIT(&priv->redirhead);

	/* Link structs together. */
	NG_NODE_SET_PRIVATE(node, priv);
	priv->node = node;

	/*
	 * libalias is not thread safe, so our node
	 * must be single threaded.
	 */
	NG_NODE_FORCE_WRITER(node);

	return (0);
}