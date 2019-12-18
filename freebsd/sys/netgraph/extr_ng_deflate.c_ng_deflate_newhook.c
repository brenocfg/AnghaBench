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
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_3__ {int compress; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_DEFLATE_HOOK_COMP ; 
 int /*<<< orphan*/  NG_DEFLATE_HOOK_DECOMP ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_deflate_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (NG_NODE_NUMHOOKS(node) > 0)
		return (EINVAL);

	if (strcmp(name, NG_DEFLATE_HOOK_COMP) == 0)
		priv->compress = 1;
	else if (strcmp(name, NG_DEFLATE_HOOK_DECOMP) == 0)
		priv->compress = 0;
	else
		return (EINVAL);

	return (0);
}