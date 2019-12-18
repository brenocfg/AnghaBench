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
struct extcon_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int find_cable_index_by_id (struct extcon_dev*,unsigned int) ; 
 int is_extcon_property_capability (struct extcon_dev*,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  is_extcon_property_supported (unsigned int,unsigned int) ; 

int extcon_get_property_capability(struct extcon_dev *edev, unsigned int id,
					unsigned int prop)
{
	int index;

	if (!edev)
		return -EINVAL;

	/* Check whether the property is supported or not */
	if (!is_extcon_property_supported(id, prop))
		return -EINVAL;

	/* Find the cable index of external connector by using id */
	index = find_cable_index_by_id(edev, id);
	if (index < 0)
		return index;

	return is_extcon_property_capability(edev, id, index, prop);
}