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
struct rail_alignment {int dummy; } ;
struct device {int dummy; } ;
struct cvb_table_freq_entry {unsigned long freq; int /*<<< orphan*/  coefficients; } ;
struct cvb_table {int /*<<< orphan*/  voltage_scale; int /*<<< orphan*/  speedo_scale; struct cvb_table_freq_entry* entries; int /*<<< orphan*/  max_millivolts; int /*<<< orphan*/  min_millivolts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN ; 
 int MAX_DVFS_FREQS ; 
 int /*<<< orphan*/  UP ; 
 int clamp (int,int,int) ; 
 int dev_pm_opp_add (struct device*,unsigned long,int) ; 
 int get_cvb_voltage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int round_cvb_voltage (int,int /*<<< orphan*/ ,struct rail_alignment*) ; 
 int round_voltage (int /*<<< orphan*/ ,struct rail_alignment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_opp_table(struct device *dev, const struct cvb_table *table,
			   struct rail_alignment *align,
			   int speedo_value, unsigned long max_freq)
{
	int i, ret, dfll_mv, min_mv, max_mv;

	min_mv = round_voltage(table->min_millivolts, align, UP);
	max_mv = round_voltage(table->max_millivolts, align, DOWN);

	for (i = 0; i < MAX_DVFS_FREQS; i++) {
		const struct cvb_table_freq_entry *entry = &table->entries[i];

		if (!entry->freq || (entry->freq > max_freq))
			break;

		dfll_mv = get_cvb_voltage(speedo_value, table->speedo_scale,
					  &entry->coefficients);
		dfll_mv = round_cvb_voltage(dfll_mv, table->voltage_scale,
					    align);
		dfll_mv = clamp(dfll_mv, min_mv, max_mv);

		ret = dev_pm_opp_add(dev, entry->freq, dfll_mv * 1000);
		if (ret)
			return ret;
	}

	return 0;
}