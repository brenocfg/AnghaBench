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
struct cvb_table {int speedo_id; int process_id; } ;

/* Variables and functions */
 int EINVAL ; 
 struct cvb_table const* ERR_PTR (int) ; 
 int build_opp_table (struct device*,struct cvb_table const*,struct rail_alignment*,int,unsigned long) ; 

const struct cvb_table *
tegra_cvb_add_opp_table(struct device *dev, const struct cvb_table *tables,
			size_t count, struct rail_alignment *align,
			int process_id, int speedo_id, int speedo_value,
			unsigned long max_freq)
{
	size_t i;
	int ret;

	for (i = 0; i < count; i++) {
		const struct cvb_table *table = &tables[i];

		if (table->speedo_id != -1 && table->speedo_id != speedo_id)
			continue;

		if (table->process_id != -1 && table->process_id != process_id)
			continue;

		ret = build_opp_table(dev, table, align, speedo_value,
				      max_freq);
		return ret ? ERR_PTR(ret) : table;
	}

	return ERR_PTR(-EINVAL);
}