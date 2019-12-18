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
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,struct ng_atmllc_priv*) ; 
 struct ng_atmllc_priv* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_atmllc_constructor(node_p node)
{
	struct	ng_atmllc_priv *priv;

	priv = malloc(sizeof(*priv), M_NETGRAPH, M_WAITOK | M_ZERO);
	NG_NODE_SET_PRIVATE(node, priv);

	return (0);
}