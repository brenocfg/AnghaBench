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
 int /*<<< orphan*/  cmm_dev ; 
 int /*<<< orphan*/  cmm_free_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmm_mem_isolate_nb ; 
 int /*<<< orphan*/  cmm_mem_nb ; 
 int /*<<< orphan*/  cmm_oom_nb ; 
 int /*<<< orphan*/  cmm_reboot_nb ; 
 scalar_t__ cmm_thread_ptr ; 
 int /*<<< orphan*/  cmm_unregister_sysfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  loaned_pages ; 
 int /*<<< orphan*/  unregister_memory_isolate_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_oom_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmm_exit(void)
{
	if (cmm_thread_ptr)
		kthread_stop(cmm_thread_ptr);
	unregister_oom_notifier(&cmm_oom_nb);
	unregister_reboot_notifier(&cmm_reboot_nb);
	unregister_memory_notifier(&cmm_mem_nb);
	unregister_memory_isolate_notifier(&cmm_mem_isolate_nb);
	cmm_free_pages(loaned_pages);
	cmm_unregister_sysfs(&cmm_dev);
}