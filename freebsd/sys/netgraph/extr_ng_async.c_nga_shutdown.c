#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_5__ {struct TYPE_5__* const sbuf; struct TYPE_5__* const abuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_ASYNC ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__* const,int) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nga_shutdown(node_p node)
{
	const sc_p sc = NG_NODE_PRIVATE(node);

	free(sc->abuf, M_NETGRAPH_ASYNC);
	free(sc->sbuf, M_NETGRAPH_ASYNC);
	bzero(sc, sizeof(*sc));
	free(sc, M_NETGRAPH_ASYNC);
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);
	return (0);
}