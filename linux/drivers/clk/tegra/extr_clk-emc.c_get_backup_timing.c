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
typedef  scalar_t__ u32 ;
struct tegra_clk_emc {int num_timings; struct emc_timing* timings; } ;
struct emc_timing {scalar_t__ ram_code; size_t parent_index; } ;

/* Variables and functions */
 scalar_t__* emc_parent_clk_sources ; 
 scalar_t__ tegra_read_ram_code () ; 

__attribute__((used)) static struct emc_timing *get_backup_timing(struct tegra_clk_emc *tegra,
					    int timing_index)
{
	int i;
	u32 ram_code = tegra_read_ram_code();
	struct emc_timing *timing;

	for (i = timing_index+1; i < tegra->num_timings; i++) {
		timing = tegra->timings + i;
		if (timing->ram_code != ram_code)
			break;

		if (emc_parent_clk_sources[timing->parent_index] !=
		    emc_parent_clk_sources[
		      tegra->timings[timing_index].parent_index])
			return timing;
	}

	for (i = timing_index-1; i >= 0; --i) {
		timing = tegra->timings + i;
		if (timing->ram_code != ram_code)
			break;

		if (emc_parent_clk_sources[timing->parent_index] !=
		    emc_parent_clk_sources[
		      tegra->timings[timing_index].parent_index])
			return timing;
	}

	return NULL;
}