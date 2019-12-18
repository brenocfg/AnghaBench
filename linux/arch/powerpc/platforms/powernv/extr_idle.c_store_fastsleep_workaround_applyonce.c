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
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  cpu_online_cores_map () ; 
 int fastsleep_workaround_applyonce ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 scalar_t__ kstrtou8 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  on_each_cpu_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pnv_fastsleep_workaround_apply ; 
 int power7_fastsleep_workaround_entry ; 
 int power7_fastsleep_workaround_exit ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 

__attribute__((used)) static ssize_t store_fastsleep_workaround_applyonce(struct device *dev,
		struct device_attribute *attr, const char *buf,
		size_t count)
{
	cpumask_t primary_thread_mask;
	int err;
	u8 val;

	if (kstrtou8(buf, 0, &val) || val != 1)
		return -EINVAL;

	if (fastsleep_workaround_applyonce == 1)
		return count;

	/*
	 * fastsleep_workaround_applyonce = 1 implies
	 * fastsleep workaround needs to be left in 'applied' state on all
	 * the cores. Do this by-
	 * 1. Disable the 'undo' workaround in fastsleep exit path
	 * 2. Sendi IPIs to all the cores which have at least one online thread
	 * 3. Disable the 'apply' workaround in fastsleep entry path
	 *
	 * There is no need to send ipi to cores which have all threads
	 * offlined, as last thread of the core entering fastsleep or deeper
	 * state would have applied workaround.
	 */
	power7_fastsleep_workaround_exit = false;

	get_online_cpus();
	primary_thread_mask = cpu_online_cores_map();
	on_each_cpu_mask(&primary_thread_mask,
				pnv_fastsleep_workaround_apply,
				&err, 1);
	put_online_cpus();
	if (err) {
		pr_err("fastsleep_workaround_applyonce change failed while running pnv_fastsleep_workaround_apply");
		goto fail;
	}

	power7_fastsleep_workaround_entry = false;

	fastsleep_workaround_applyonce = 1;

	return count;
fail:
	return -EIO;
}