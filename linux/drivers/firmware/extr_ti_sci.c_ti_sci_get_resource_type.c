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
typedef  scalar_t__ u16 ;
struct ti_sci_rm_type_map {scalar_t__ dev_id; scalar_t__ type; } ;
struct ti_sci_info {TYPE_1__* desc; } ;
struct TYPE_2__ {struct ti_sci_rm_type_map* rm_type_map; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ti_sci_get_resource_type(struct ti_sci_info *info, u16 dev_id,
				    u16 *type)
{
	struct ti_sci_rm_type_map *rm_type_map = info->desc->rm_type_map;
	bool found = false;
	int i;

	/* If map is not provided then assume dev_id is used as type */
	if (!rm_type_map) {
		*type = dev_id;
		return 0;
	}

	for (i = 0; rm_type_map[i].dev_id; i++) {
		if (rm_type_map[i].dev_id == dev_id) {
			*type = rm_type_map[i].type;
			found = true;
			break;
		}
	}

	if (!found)
		return -EINVAL;

	return 0;
}