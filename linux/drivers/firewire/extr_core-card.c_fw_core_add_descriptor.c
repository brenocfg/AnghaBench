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
struct fw_descriptor {size_t length; int* data; scalar_t__ immediate; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  card_mutex ; 
 int config_rom_length ; 
 int /*<<< orphan*/  descriptor_count ; 
 int /*<<< orphan*/  descriptor_list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int required_space (struct fw_descriptor*) ; 
 int /*<<< orphan*/  update_config_roms () ; 

int fw_core_add_descriptor(struct fw_descriptor *desc)
{
	size_t i;
	int ret;

	/*
	 * Check descriptor is valid; the length of all blocks in the
	 * descriptor has to add up to exactly the length of the
	 * block.
	 */
	i = 0;
	while (i < desc->length)
		i += (desc->data[i] >> 16) + 1;

	if (i != desc->length)
		return -EINVAL;

	mutex_lock(&card_mutex);

	if (config_rom_length + required_space(desc) > 256) {
		ret = -EBUSY;
	} else {
		list_add_tail(&desc->link, &descriptor_list);
		config_rom_length += required_space(desc);
		descriptor_count++;
		if (desc->immediate > 0)
			descriptor_count++;
		update_config_roms();
		ret = 0;
	}

	mutex_unlock(&card_mutex);

	return ret;
}