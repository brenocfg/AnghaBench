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

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int RM_NOWITNESS ; 
 int RM_RECURSE ; 
 int /*<<< orphan*/  SX_NOWITNESS ; 
 int /*<<< orphan*/  mac_labelzone_init () ; 
 int /*<<< orphan*/  mac_policy_list ; 
 int /*<<< orphan*/  mac_policy_rm ; 
 int /*<<< orphan*/  mac_policy_sx ; 
 int /*<<< orphan*/  mac_static_policy_list ; 
 int /*<<< orphan*/  rm_init_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sx_init_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mac_init(void)
{

	LIST_INIT(&mac_static_policy_list);
	LIST_INIT(&mac_policy_list);
	mac_labelzone_init();

#ifndef MAC_STATIC
	rm_init_flags(&mac_policy_rm, "mac_policy_rm", RM_NOWITNESS |
	    RM_RECURSE);
	sx_init_flags(&mac_policy_sx, "mac_policy_sx", SX_NOWITNESS);
#endif
}