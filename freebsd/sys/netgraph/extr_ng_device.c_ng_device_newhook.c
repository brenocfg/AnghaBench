#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG ; 
 int EISCONN ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_device_newhook(node_p node, hook_p hook, const char *name)
{
	priv_p priv = NG_NODE_PRIVATE(node);

	DBG;

	/* We have only one hook per node */
	if (priv->hook != NULL)
		return (EISCONN);

	priv->hook = hook;

	return(0);
}