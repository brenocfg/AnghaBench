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
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_btsocket_l2cap_raw_node_connect(hook_p hook)
{
	NG_HOOK_SET_PRIVATE(hook, NULL);
	NG_HOOK_REF(hook); /* Keep extra reference to the hook */

	return (0);
}