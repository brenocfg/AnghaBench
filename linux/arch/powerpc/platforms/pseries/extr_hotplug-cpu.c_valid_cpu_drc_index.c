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
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_u32_index (struct device_node*,char*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool valid_cpu_drc_index(struct device_node *parent, u32 drc_index)
{
	bool found = false;
	int rc, index;

	index = 0;
	while (!found) {
		u32 drc;

		rc = of_property_read_u32_index(parent, "ibm,drc-indexes",
						index++, &drc);
		if (rc)
			break;

		if (drc == drc_index)
			found = true;
	}

	return found;
}