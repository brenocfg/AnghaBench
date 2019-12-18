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
typedef  int /*<<< orphan*/  sc_p ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_source_clr_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_source_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_source_rmnode(node_p node)
{
	sc_p sc = NG_NODE_PRIVATE(node);

	ng_source_stop(sc);
	ng_source_clr_data(sc);
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);
	free(sc, M_NETGRAPH);

	return (0);
}