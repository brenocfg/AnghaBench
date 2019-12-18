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
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_free_cpufreq_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freq_table ; 
 int /*<<< orphan*/  freq_table_users ; 
 int /*<<< orphan*/  mpu_dev ; 

__attribute__((used)) static inline void freq_table_free(void)
{
	if (atomic_dec_and_test(&freq_table_users))
		dev_pm_opp_free_cpufreq_table(mpu_dev, &freq_table);
}