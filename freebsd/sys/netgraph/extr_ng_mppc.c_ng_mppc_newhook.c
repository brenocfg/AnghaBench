#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_6__ {int /*<<< orphan*/ * hook; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hook; } ;
struct TYPE_7__ {TYPE_2__ recv; TYPE_1__ xmit; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_MPPC_HOOK_COMP ; 
 int /*<<< orphan*/  NG_MPPC_HOOK_DECOMP ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_mppc_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	hook_p *hookPtr;

	/* Check hook name */
	if (strcmp(name, NG_MPPC_HOOK_COMP) == 0)
		hookPtr = &priv->xmit.hook;
	else if (strcmp(name, NG_MPPC_HOOK_DECOMP) == 0)
		hookPtr = &priv->recv.hook;
	else
		return (EINVAL);

	/* See if already connected */
	if (*hookPtr != NULL)
		return (EISCONN);

	/* OK */
	*hookPtr = hook;
	return (0);
}