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
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  syscfg; struct device* cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR_ID_INDEX ; 
 unsigned int VERSION_SHIFT ; 
 TYPE_1__ ddata ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int of_property_read_u32_index (struct device_node*,char*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int sti_cpufreq_fetch_major(void) {
	struct device_node *np = ddata.cpu->of_node;
	struct device *dev = ddata.cpu;
	unsigned int major_offset;
	unsigned int socid;
	int ret;

	ret = of_property_read_u32_index(np, "st,syscfg",
					 MAJOR_ID_INDEX, &major_offset);
	if (ret) {
		dev_err(dev, "No major number offset provided in %pOF [%d]\n",
			np, ret);
		return ret;
	}

	ret = regmap_read(ddata.syscfg, major_offset, &socid);
	if (ret) {
		dev_err(dev, "Failed to read major number from syscon [%d]\n",
			ret);
		return ret;
	}

	return ((socid >> VERSION_SHIFT) & 0xf) + 1;
}