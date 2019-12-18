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
struct notifier_block {int dummy; } ;
struct clk_notifier_data {scalar_t__ new_rate; scalar_t__ old_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  HB_CPUFREQ_VOLT_RETRIES ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 unsigned long POST_RATE_CHANGE ; 
 unsigned long PRE_RATE_CHANGE ; 
 scalar_t__ hb_voltage_change (scalar_t__) ; 

__attribute__((used)) static int hb_cpufreq_clk_notify(struct notifier_block *nb,
				unsigned long action, void *hclk)
{
	struct clk_notifier_data *clk_data = hclk;
	int i = 0;

	if (action == PRE_RATE_CHANGE) {
		if (clk_data->new_rate > clk_data->old_rate)
			while (hb_voltage_change(clk_data->new_rate))
				if (i++ > HB_CPUFREQ_VOLT_RETRIES)
					return NOTIFY_BAD;
	} else if (action == POST_RATE_CHANGE) {
		if (clk_data->new_rate < clk_data->old_rate)
			while (hb_voltage_change(clk_data->new_rate))
				if (i++ > HB_CPUFREQ_VOLT_RETRIES)
					return NOTIFY_BAD;
	}

	return NOTIFY_DONE;
}