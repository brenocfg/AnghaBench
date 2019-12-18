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
struct ti_cpufreq_data {TYPE_1__* soc_data; int /*<<< orphan*/  syscon; struct device* cpu_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rev_offset; } ;

/* Variables and functions */
 int BIT (int) ; 
 int REVISION_MASK ; 
 int REVISION_SHIFT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ti_cpufreq_get_rev(struct ti_cpufreq_data *opp_data,
			      u32 *revision_value)
{
	struct device *dev = opp_data->cpu_dev;
	u32 revision;
	int ret;

	ret = regmap_read(opp_data->syscon, opp_data->soc_data->rev_offset,
			  &revision);
	if (ret) {
		dev_err(dev,
			"Failed to read the revision number from syscon: %d\n",
			ret);
		return ret;
	}

	*revision_value = BIT((revision >> REVISION_SHIFT) & REVISION_MASK);

	return 0;
}