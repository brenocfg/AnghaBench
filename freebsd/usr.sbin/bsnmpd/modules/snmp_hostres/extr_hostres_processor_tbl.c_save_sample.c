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
struct processor_entry {int cur_sample_idx; long** states; int sample_cnt; int /*<<< orphan*/  load; int /*<<< orphan*/  cpu_no; } ;

/* Variables and functions */
 int CPUSTATES ; 
 int /*<<< orphan*/  HRDBG (char*,int /*<<< orphan*/ ,int) ; 
 int MAX_CPU_SAMPLES ; 
 int /*<<< orphan*/  get_avg_load (struct processor_entry*) ; 

__attribute__((used)) static void
save_sample(struct processor_entry *e, long *cp_times)
{
	int i;

	e->cur_sample_idx = (e->cur_sample_idx + 1) % MAX_CPU_SAMPLES;
	for (i = 0; cp_times != NULL && i < CPUSTATES; i++)
		e->states[e->cur_sample_idx][i] = cp_times[i];

	e->sample_cnt++;
	if (e->sample_cnt > MAX_CPU_SAMPLES)
		e->sample_cnt = MAX_CPU_SAMPLES;

	HRDBG("sample count for CPU no. %d went to %d", e->cpu_no, e->sample_cnt);
	e->load = get_avg_load(e);

}