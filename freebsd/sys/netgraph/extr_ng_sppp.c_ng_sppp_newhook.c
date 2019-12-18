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
typedef  scalar_t__ hook_p ;
struct TYPE_4__ {scalar_t__ hook; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (scalar_t__,TYPE_1__*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SPPP_HOOK_DOWNSTREAM ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_sppp_newhook (node_p node, hook_p hook, const char *name)
{
	priv_p priv = NG_NODE_PRIVATE (node);

	if (strcmp (name, NG_SPPP_HOOK_DOWNSTREAM) != 0)
		return (EINVAL);
	
	if (priv->hook)
		return (EISCONN);
		
	priv->hook = hook;
	NG_HOOK_SET_PRIVATE (hook, priv);
	
	return (0);
}