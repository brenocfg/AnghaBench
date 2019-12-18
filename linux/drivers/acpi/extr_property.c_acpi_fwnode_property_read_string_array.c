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
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PROP_STRING ; 
 int acpi_node_prop_read (struct fwnode_handle const*,char const*,int /*<<< orphan*/ ,char const**,size_t) ; 

__attribute__((used)) static int
acpi_fwnode_property_read_string_array(const struct fwnode_handle *fwnode,
				       const char *propname, const char **val,
				       size_t nval)
{
	return acpi_node_prop_read(fwnode, propname, DEV_PROP_STRING,
				   val, nval);
}