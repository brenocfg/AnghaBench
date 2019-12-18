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
typedef  scalar_t__ u64 ;
struct p4_event_bind {int /*<<< orphan*/ * escr_msr; } ;
struct hw_perf_event {int idx; scalar_t__ config; } ;
struct cpu_hw_events {TYPE_1__** event_list; } ;
struct TYPE_2__ {struct hw_perf_event hw; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  P4_ESCR_MSR_TABLE_SIZE ; 
 int /*<<< orphan*/  X86_PMC_IDX_MAX ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int /*<<< orphan*/ ) ; 
 struct p4_event_bind* p4_config_get_bind (scalar_t__) ; 
 scalar_t__ p4_get_alias_event (scalar_t__) ; 
 int p4_get_escr_idx (int /*<<< orphan*/ ) ; 
 unsigned int p4_ht_thread (int) ; 
 int p4_next_cntr (unsigned int,unsigned long*,struct p4_event_bind*) ; 
 int /*<<< orphan*/  p4_pmu_swap_config_ts (struct hw_perf_event*,int) ; 
 scalar_t__ p4_should_swap_ts (scalar_t__,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int smp_processor_id () ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int p4_pmu_schedule_events(struct cpu_hw_events *cpuc, int n, int *assign)
{
	unsigned long used_mask[BITS_TO_LONGS(X86_PMC_IDX_MAX)];
	unsigned long escr_mask[BITS_TO_LONGS(P4_ESCR_MSR_TABLE_SIZE)];
	int cpu = smp_processor_id();
	struct hw_perf_event *hwc;
	struct p4_event_bind *bind;
	unsigned int i, thread, num;
	int cntr_idx, escr_idx;
	u64 config_alias;
	int pass;

	bitmap_zero(used_mask, X86_PMC_IDX_MAX);
	bitmap_zero(escr_mask, P4_ESCR_MSR_TABLE_SIZE);

	for (i = 0, num = n; i < n; i++, num--) {

		hwc = &cpuc->event_list[i]->hw;
		thread = p4_ht_thread(cpu);
		pass = 0;

again:
		/*
		 * It's possible to hit a circular lock
		 * between original and alternative events
		 * if both are scheduled already.
		 */
		if (pass > 2)
			goto done;

		bind = p4_config_get_bind(hwc->config);
		escr_idx = p4_get_escr_idx(bind->escr_msr[thread]);
		if (unlikely(escr_idx == -1))
			goto done;

		if (hwc->idx != -1 && !p4_should_swap_ts(hwc->config, cpu)) {
			cntr_idx = hwc->idx;
			if (assign)
				assign[i] = hwc->idx;
			goto reserve;
		}

		cntr_idx = p4_next_cntr(thread, used_mask, bind);
		if (cntr_idx == -1 || test_bit(escr_idx, escr_mask)) {
			/*
			 * Check whether an event alias is still available.
			 */
			config_alias = p4_get_alias_event(hwc->config);
			if (!config_alias)
				goto done;
			hwc->config = config_alias;
			pass++;
			goto again;
		}
		/*
		 * Perf does test runs to see if a whole group can be assigned
		 * together successfully.  There can be multiple rounds of this.
		 * Unfortunately, p4_pmu_swap_config_ts touches the hwc->config
		 * bits, such that the next round of group assignments will
		 * cause the above p4_should_swap_ts to pass instead of fail.
		 * This leads to counters exclusive to thread0 being used by
		 * thread1.
		 *
		 * Solve this with a cheap hack, reset the idx back to -1 to
		 * force a new lookup (p4_next_cntr) to get the right counter
		 * for the right thread.
		 *
		 * This probably doesn't comply with the general spirit of how
		 * perf wants to work, but P4 is special. :-(
		 */
		if (p4_should_swap_ts(hwc->config, cpu))
			hwc->idx = -1;
		p4_pmu_swap_config_ts(hwc, cpu);
		if (assign)
			assign[i] = cntr_idx;
reserve:
		set_bit(cntr_idx, used_mask);
		set_bit(escr_idx, escr_mask);
	}

done:
	return num ? -EINVAL : 0;
}