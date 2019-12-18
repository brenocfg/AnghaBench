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
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  ng_destroy_hook (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_rmhook_part2(node_p node, hook_p hook, void *arg1, int arg2)
{
	ng_destroy_hook(hook);
	return ;
}