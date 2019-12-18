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
struct intel_raid_vol {struct intel_raid_map* map; scalar_t__ migr_state; } ;
struct intel_raid_map {size_t total_disks; int /*<<< orphan*/ * disk_idx; } ;

/* Variables and functions */

__attribute__((used)) static struct intel_raid_map *
intel_get_map(struct intel_raid_vol *mvol, int i)
{
	struct intel_raid_map *mmap;

	if (i > (mvol->migr_state ? 1 : 0))
		return (NULL);
	mmap = &mvol->map[0];
	for (; i > 0; i--) {
		mmap = (struct intel_raid_map *)
		    &mmap->disk_idx[mmap->total_disks];
	}
	return ((struct intel_raid_map *)mmap);
}