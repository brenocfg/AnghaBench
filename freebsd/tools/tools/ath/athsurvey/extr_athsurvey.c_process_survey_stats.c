#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {TYPE_1__* samples; } ;
struct TYPE_4__ {int cycle_count; scalar_t__ ext_chan_busy; scalar_t__ chan_busy; scalar_t__ rx_busy; scalar_t__ tx_busy; } ;
typedef  TYPE_2__ HAL_CHANNEL_SURVEY ;

/* Variables and functions */
 int CHANNEL_SURVEY_SAMPLE_COUNT ; 
 int /*<<< orphan*/  printf (char*,float,float,float,float) ; 

__attribute__((used)) static void
process_survey_stats(HAL_CHANNEL_SURVEY *hs)
{
	int i;
	float tx = 0.0, rx = 0.0, cc = 0.0, cext = 0.0;
	float max_tx = 0.0, max_rx = 0.0, max_cc = 0.0, max_cext = 0.0;
	uint64_t avg_tx = 0, avg_rx = 0, avg_cc = 0, avg_cext = 0;
	float min_tx = 100.0, min_rx = 100.0, min_cc = 100.0, min_cext = 100.0;
	int n = 0;
	int cycle_count = 0, max_cycle_count = 0;

	/* Calculate a percentage channel busy */
	for (i = 0; i < CHANNEL_SURVEY_SAMPLE_COUNT; i++) {
		/*
		 * Skip samples with no cycle count
		 */
		if (hs->samples[i].cycle_count == 0)
			continue;
		n++;

		/*
		 * Grab cycle count, calculate maximum just for curiousity
		 */
		cycle_count = hs->samples[i].cycle_count;
		if (cycle_count > max_cycle_count)
			max_cycle_count = cycle_count;

		/*
		 * Calculate percentage
		 */
		tx = (float) hs->samples[i].tx_busy * 100.0 /
		    hs->samples[i].cycle_count;
		rx = (float) hs->samples[i].rx_busy * 100.0 /
		    hs->samples[i].cycle_count;
		cc = (float) hs->samples[i].chan_busy * 100.0 /
		    hs->samples[i].cycle_count;
		cext = (float) hs->samples[i].ext_chan_busy * 100.0 /
		    hs->samples[i].cycle_count;

		/*
		 * Update rolling average
		 * XXX to preserve some accuracy, keep two decimal points
		 * using "fixed" point math.
		 */
		avg_tx += (uint64_t) hs->samples[i].tx_busy * 10000 /
		    hs->samples[i].cycle_count;
		avg_rx += (uint64_t) hs->samples[i].rx_busy * 10000 /
		    hs->samples[i].cycle_count;
		avg_cc += (uint64_t) hs->samples[i].chan_busy * 10000 /
		    hs->samples[i].cycle_count;
		avg_cext += (uint64_t) hs->samples[i].ext_chan_busy * 10000 /
		    hs->samples[i].cycle_count;

		/*
		 * Update maximum values
		 */
		if (tx > max_tx)
			max_tx = tx;
		if (rx > max_rx)
			max_rx = rx;
		if (cc > max_cc)
			max_cc = cc;
		if (cext > max_cext)
			max_cext = cext;

		/*
		 * Update minimum values
		 */
		if (tx < min_tx)
			min_tx = tx;
		if (rx < min_rx)
			min_rx = rx;
		if (cc < min_cc)
			min_cc = cc;
		if (cext < min_cext)
			min_cext = cext;
	}

	printf("(%4.1f %4.1f %4.1f %4.1f) ",
	    min_tx, min_rx, min_cc, min_cext);
	printf("(%4.1f %4.1f %4.1f %4.1f) ",
	    n == 0 ? 0.0 : (float) (avg_tx / n) / 100.0,
	    n == 0 ? 0.0 : (float) (avg_rx / n) / 100.0,
	    n == 0 ? 0.0 : (float) (avg_cc / n) / 100.0,
	    n == 0 ? 0.0 : (float) (avg_cext / n) / 100.0);
	printf("(%4.1f %4.1f %4.1f %4.1f)\n",
	    max_tx, max_rx, max_cc, max_cext);
}