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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ *,int) ; 
 int pkeys_devtree_defined ; 
 int /*<<< orphan*/  pkeys_total ; 

__attribute__((used)) static void scan_pkey_feature(void)
{
	u32 vals[2];
	struct device_node *cpu;

	cpu = of_find_node_by_type(NULL, "cpu");
	if (!cpu)
		return;

	if (of_property_read_u32_array(cpu,
			"ibm,processor-storage-keys", vals, 2))
		return;

	/*
	 * Since any pkey can be used for data or execute, we will just treat
	 * all keys as equal and track them as one entity.
	 */
	pkeys_total = vals[0];
	pkeys_devtree_defined = true;
}