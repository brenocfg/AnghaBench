#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
struct TYPE_5__ {int /*<<< orphan*/  stats; void* dest; void* hook; } ;
struct TYPE_4__ {TYPE_3__ upper; TYPE_3__ lower; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_CAR_HOOK_LOWER ; 
 int /*<<< orphan*/  NG_CAR_HOOK_UPPER ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,TYPE_3__*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_car_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_CAR_HOOK_LOWER) == 0) {
		priv->lower.hook = hook;
		priv->upper.dest = hook;
		bzero(&priv->lower.stats, sizeof(priv->lower.stats));
		NG_HOOK_SET_PRIVATE(hook, &priv->lower);
	} else if (strcmp(name, NG_CAR_HOOK_UPPER) == 0) {
		priv->upper.hook = hook;
		priv->lower.dest = hook;
		bzero(&priv->upper.stats, sizeof(priv->upper.stats));
		NG_HOOK_SET_PRIVATE(hook, &priv->upper);
	} else
		return (EINVAL);
	return(0);
}