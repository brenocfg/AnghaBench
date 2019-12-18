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
struct software_node {struct property_entry* properties; } ;
struct property_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct property_entry*) ; 
 int PTR_ERR (struct property_entry*) ; 
 struct property_entry* property_entries_dup (struct property_entry const*) ; 

__attribute__((used)) static int
software_node_register_properties(struct software_node *node,
				  const struct property_entry *properties)
{
	struct property_entry *props;

	props = property_entries_dup(properties);
	if (IS_ERR(props))
		return PTR_ERR(props);

	node->properties = props;

	return 0;
}