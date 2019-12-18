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

/* Variables and functions */
 int /*<<< orphan*/  devp_offset_find (void const*) ; 
 int /*<<< orphan*/  fdt ; 
 int fdt_node_offset_by_prop_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int) ; 
 void* offset_devp (int) ; 

__attribute__((used)) static void *fdt_wrapper_find_node_by_prop_value(const void *prev,
						 const char *name,
						 const char *val,
						 int len)
{
	int offset = fdt_node_offset_by_prop_value(fdt, devp_offset_find(prev),
	                                           name, val, len);
	return offset_devp(offset);
}