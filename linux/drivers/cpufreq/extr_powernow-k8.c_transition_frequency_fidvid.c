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
typedef  int u32 ;
struct powernow_k8_data {int currvid; int currfid; TYPE_1__* powernow_table; } ;
struct cpufreq_policy {int dummy; } ;
struct cpufreq_freqs {void* new; void* old; } ;
struct TYPE_2__ {int driver_data; } ;

/* Variables and functions */
 struct cpufreq_policy* cpufreq_cpu_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_begin (struct cpufreq_policy*,struct cpufreq_freqs*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_end (struct cpufreq_policy*,struct cpufreq_freqs*,int) ; 
 void* find_khz_freq_from_fid (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 scalar_t__ query_current_values_with_pending_wait (struct powernow_k8_data*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int transition_fid_vid (struct powernow_k8_data*,int,int) ; 

__attribute__((used)) static int transition_frequency_fidvid(struct powernow_k8_data *data,
		unsigned int index)
{
	struct cpufreq_policy *policy;
	u32 fid = 0;
	u32 vid = 0;
	int res;
	struct cpufreq_freqs freqs;

	pr_debug("cpu %d transition to index %u\n", smp_processor_id(), index);

	/* fid/vid correctness check for k8 */
	/* fid are the lower 8 bits of the index we stored into
	 * the cpufreq frequency table in find_psb_table, vid
	 * are the upper 8 bits.
	 */
	fid = data->powernow_table[index].driver_data & 0xFF;
	vid = (data->powernow_table[index].driver_data & 0xFF00) >> 8;

	pr_debug("table matched fid 0x%x, giving vid 0x%x\n", fid, vid);

	if (query_current_values_with_pending_wait(data))
		return 1;

	if ((data->currvid == vid) && (data->currfid == fid)) {
		pr_debug("target matches current values (fid 0x%x, vid 0x%x)\n",
			fid, vid);
		return 0;
	}

	pr_debug("cpu %d, changing to fid 0x%x, vid 0x%x\n",
		smp_processor_id(), fid, vid);
	freqs.old = find_khz_freq_from_fid(data->currfid);
	freqs.new = find_khz_freq_from_fid(fid);

	policy = cpufreq_cpu_get(smp_processor_id());
	cpufreq_cpu_put(policy);

	cpufreq_freq_transition_begin(policy, &freqs);
	res = transition_fid_vid(data, fid, vid);
	cpufreq_freq_transition_end(policy, &freqs, res);

	return res;
}