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
typedef  int /*<<< orphan*/ * node_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/ * NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_deadnode ; 
 int /*<<< orphan*/  ng_rmhook_part2 ; 
 int ng_send_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ng_rmhook_self(hook_p hook)
{
	int		error;
	node_p node = NG_HOOK_NODE(hook);

	if (node == &ng_deadnode)
		return (0);

	error = ng_send_fn(node, hook, &ng_rmhook_part2, NULL, 0);
	return (error);
}