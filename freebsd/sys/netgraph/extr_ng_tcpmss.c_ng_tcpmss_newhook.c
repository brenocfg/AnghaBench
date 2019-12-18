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
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_tcpmss_newhook(node_p node, hook_p hook, const char *name)
{
	hpriv_p priv;

	priv = malloc(sizeof(*priv), M_NETGRAPH, M_NOWAIT | M_ZERO);
	if (priv == NULL)
		return (ENOMEM);

	NG_HOOK_SET_PRIVATE(hook, priv);

	return (0);
}