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
 int /*<<< orphan*/  cpufreq_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scpi_cpufreq_driver ; 
 int /*<<< orphan*/ * scpi_ops ; 

__attribute__((used)) static int scpi_cpufreq_remove(struct platform_device *pdev)
{
	cpufreq_unregister_driver(&scpi_cpufreq_driver);
	scpi_ops = NULL;
	return 0;
}