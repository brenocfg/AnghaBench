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
typedef  size_t u_int ;
struct processor_entry {int sample_cnt; int cur_sample_idx; int /*<<< orphan*/  cpu_no; scalar_t__** states; } ;

/* Variables and functions */
 size_t CPUSTATES ; 
 int /*<<< orphan*/  HRDBG (char*,int /*<<< orphan*/ ,long,double) ; 
 int MAX_CPU_SAMPLES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_avg_load(struct processor_entry *e)
{
	u_int i, oldest;
	long delta = 0;
	double usage = 0.0;

	assert(e != NULL);

	/* Need two samples to perform delta calculation. */
	if (e->sample_cnt <= 1)
		return (0);

	/* Oldest usable index, we wrap around. */
	if (e->sample_cnt == MAX_CPU_SAMPLES)
		oldest = (e->cur_sample_idx + 1) % MAX_CPU_SAMPLES;
	else
		oldest = 0;

	/* Sum delta for all states. */
	for (i = 0; i < CPUSTATES; i++) {
		delta += e->states[e->cur_sample_idx][i];
		delta -= e->states[oldest][i];
	}
	if (delta == 0)
		return 0;

	/* Take idle time from the last element and convert to
	 * percent usage by contrasting with total ticks delta. */
	usage = (double)(e->states[e->cur_sample_idx][CPUSTATES-1] -
	    e->states[oldest][CPUSTATES-1]) / delta;
	usage = 100 - (usage * 100);
	HRDBG("CPU no. %d, delta ticks %ld, pct usage %.2f", e->cpu_no,
	    delta, usage);

	return ((int)(usage));
}