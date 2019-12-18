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
 int /*<<< orphan*/  __null_setup_fault (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_requeue_str ; 
 int /*<<< orphan*/  g_timeout_str ; 
 int /*<<< orphan*/  null_requeue_attr ; 
 int /*<<< orphan*/  null_timeout_attr ; 

__attribute__((used)) static bool null_setup_fault(void)
{
#ifdef CONFIG_BLK_DEV_NULL_BLK_FAULT_INJECTION
	if (!__null_setup_fault(&null_timeout_attr, g_timeout_str))
		return false;
	if (!__null_setup_fault(&null_requeue_attr, g_requeue_str))
		return false;
#endif
	return true;
}