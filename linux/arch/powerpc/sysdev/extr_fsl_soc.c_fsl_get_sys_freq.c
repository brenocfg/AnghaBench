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
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

u32 fsl_get_sys_freq(void)
{
	static u32 sysfreq = -1;
	struct device_node *soc;

	if (sysfreq != -1)
		return sysfreq;

	soc = of_find_node_by_type(NULL, "soc");
	if (!soc)
		return -1;

	of_property_read_u32(soc, "clock-frequency", &sysfreq);
	if (sysfreq == -1 || !sysfreq)
		of_property_read_u32(soc, "bus-frequency", &sysfreq);

	of_node_put(soc);
	return sysfreq;
}