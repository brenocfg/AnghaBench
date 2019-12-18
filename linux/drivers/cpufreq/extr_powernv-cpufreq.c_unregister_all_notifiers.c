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
 int /*<<< orphan*/  OPAL_MSG_OCC ; 
 int /*<<< orphan*/  opal_message_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powernv_cpufreq_opal_nb ; 
 int /*<<< orphan*/  powernv_cpufreq_reboot_nb ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void unregister_all_notifiers(void)
{
	opal_message_notifier_unregister(OPAL_MSG_OCC,
					 &powernv_cpufreq_opal_nb);
	unregister_reboot_notifier(&powernv_cpufreq_reboot_nb);
}