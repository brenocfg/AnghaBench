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
struct ng_atmllc_priv {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 struct ng_atmllc_priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ng_atmllc_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_atmllc_shutdown(node_p node)
{
	struct	ng_atmllc_priv *priv;

	priv = NG_NODE_PRIVATE(node);

	free(priv, M_NETGRAPH);

	NG_NODE_UNREF(node);

	return (0);
}