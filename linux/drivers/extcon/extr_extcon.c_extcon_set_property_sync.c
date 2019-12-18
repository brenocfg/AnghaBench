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
typedef  union extcon_property_value {int dummy; } extcon_property_value ;
struct extcon_dev {int dummy; } ;

/* Variables and functions */
 int extcon_set_property (struct extcon_dev*,unsigned int,unsigned int,union extcon_property_value) ; 
 int extcon_sync (struct extcon_dev*,unsigned int) ; 

int extcon_set_property_sync(struct extcon_dev *edev, unsigned int id,
				unsigned int prop,
				union extcon_property_value prop_val)
{
	int ret;

	ret = extcon_set_property(edev, id, prop, prop_val);
	if (ret < 0)
		return ret;

	return extcon_sync(edev, id);
}