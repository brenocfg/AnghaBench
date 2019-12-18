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
struct hws_qsi_info_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*) ; 
 unsigned long freq_to_sample_rate (struct hws_qsi_info_block*,unsigned long) ; 
 unsigned long hw_limit_rate (struct hws_qsi_info_block*,unsigned long) ; 
 scalar_t__ sample_rate_to_freq (struct hws_qsi_info_block*,unsigned long) ; 
 int /*<<< orphan*/  sfdbg ; 
 scalar_t__ sysctl_perf_event_sample_rate ; 

__attribute__((used)) static unsigned long getrate(bool freq, unsigned long sample,
			     struct hws_qsi_info_block *si)
{
	unsigned long rate;

	if (freq) {
		rate = freq_to_sample_rate(si, sample);
		rate = hw_limit_rate(si, rate);
	} else {
		/* The min/max sampling rates specifies the valid range
		 * of sample periods.  If the specified sample period is
		 * out of range, limit the period to the range boundary.
		 */
		rate = hw_limit_rate(si, sample);

		/* The perf core maintains a maximum sample rate that is
		 * configurable through the sysctl interface.  Ensure the
		 * sampling rate does not exceed this value.  This also helps
		 * to avoid throttling when pushing samples with
		 * perf_event_overflow().
		 */
		if (sample_rate_to_freq(si, rate) >
		    sysctl_perf_event_sample_rate) {
			debug_sprintf_event(sfdbg, 1,
					    "Sampling rate exceeds maximum "
					    "perf sample rate\n");
			rate = 0;
		}
	}
	return rate;
}