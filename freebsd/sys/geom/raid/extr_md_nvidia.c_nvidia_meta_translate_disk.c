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
struct nvidia_raid_conf {scalar_t__ type; int array_width; } ;

/* Variables and functions */
 scalar_t__ NVIDIA_T_RAID01 ; 

__attribute__((used)) static int
nvidia_meta_translate_disk(struct nvidia_raid_conf *meta, int md_disk_pos)
{
	int disk_pos;

	if (md_disk_pos >= 0 && meta->type == NVIDIA_T_RAID01) {
		disk_pos = (md_disk_pos / meta->array_width) +
		    (md_disk_pos % meta->array_width) * meta->array_width;
	} else
		disk_pos = md_disk_pos;
	return (disk_pos);
}