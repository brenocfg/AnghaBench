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
struct property_entry {size_t length; } ;

/* Variables and functions */
 int EINVAL ; 
 struct property_entry* property_entry_get (struct property_entry const*,char const*) ; 

__attribute__((used)) static int
property_entry_count_elems_of_size(const struct property_entry *props,
				   const char *propname, size_t length)
{
	const struct property_entry *prop;

	prop = property_entry_get(props, propname);
	if (!prop)
		return -EINVAL;

	return prop->length / length;
}