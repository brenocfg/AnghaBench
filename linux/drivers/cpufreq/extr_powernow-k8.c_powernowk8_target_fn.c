#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct powernowk8_target_arg {unsigned int newstate; struct cpufreq_policy* pol; } ;
struct powernow_k8_data {scalar_t__ currfid; scalar_t__ currvid; TYPE_1__* powernow_table; } ;
struct cpufreq_policy {int /*<<< orphan*/  cur; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 long EINVAL ; 
 long EIO ; 
 int /*<<< orphan*/  fidvid_mutex ; 
 int /*<<< orphan*/  find_khz_freq_from_fid (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pending_bit_stuck () ; 
 struct powernow_k8_data* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernow_data ; 
 int /*<<< orphan*/  powernow_k8_acpi_pst_values (struct powernow_k8_data*,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ query_current_values_with_pending_wait (struct powernow_k8_data*) ; 
 int transition_frequency_fidvid (struct powernow_k8_data*,unsigned int) ; 

__attribute__((used)) static long powernowk8_target_fn(void *arg)
{
	struct powernowk8_target_arg *pta = arg;
	struct cpufreq_policy *pol = pta->pol;
	unsigned newstate = pta->newstate;
	struct powernow_k8_data *data = per_cpu(powernow_data, pol->cpu);
	u32 checkfid;
	u32 checkvid;
	int ret;

	if (!data)
		return -EINVAL;

	checkfid = data->currfid;
	checkvid = data->currvid;

	if (pending_bit_stuck()) {
		pr_err("failing targ, change pending bit set\n");
		return -EIO;
	}

	pr_debug("targ: cpu %d, %d kHz, min %d, max %d\n",
		pol->cpu, data->powernow_table[newstate].frequency, pol->min,
		pol->max);

	if (query_current_values_with_pending_wait(data))
		return -EIO;

	pr_debug("targ: curr fid 0x%x, vid 0x%x\n",
		data->currfid, data->currvid);

	if ((checkvid != data->currvid) ||
	    (checkfid != data->currfid)) {
		pr_info("error - out of sync, fix 0x%x 0x%x, vid 0x%x 0x%x\n",
		       checkfid, data->currfid,
		       checkvid, data->currvid);
	}

	mutex_lock(&fidvid_mutex);

	powernow_k8_acpi_pst_values(data, newstate);

	ret = transition_frequency_fidvid(data, newstate);

	if (ret) {
		pr_err("transition frequency failed\n");
		mutex_unlock(&fidvid_mutex);
		return 1;
	}
	mutex_unlock(&fidvid_mutex);

	pol->cur = find_khz_freq_from_fid(data->currfid);

	return 0;
}