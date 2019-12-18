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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  cpufreq_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpufreq_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ls1x_cpufreq_driver ; 
 int /*<<< orphan*/  ls1x_cpufreq_notifier_block ; 

__attribute__((used)) static int ls1x_cpufreq_remove(struct platform_device *pdev)
{
	cpufreq_unregister_notifier(&ls1x_cpufreq_notifier_block,
				    CPUFREQ_TRANSITION_NOTIFIER);
	cpufreq_unregister_driver(&ls1x_cpufreq_driver);

	return 0;
}