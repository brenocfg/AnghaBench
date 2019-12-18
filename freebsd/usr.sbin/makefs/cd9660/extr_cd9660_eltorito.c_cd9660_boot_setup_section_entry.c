#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cd9660_boot_image {int /*<<< orphan*/  sector; int /*<<< orphan*/  num_sectors; int /*<<< orphan*/  loadSegment; int /*<<< orphan*/  targetMode; } ;
struct TYPE_4__ {int /*<<< orphan*/  load_rba; int /*<<< orphan*/  sector_count; int /*<<< orphan*/  load_segment; int /*<<< orphan*/ * media_type; int /*<<< orphan*/ * boot_indicator; } ;
struct TYPE_3__ {TYPE_2__ SE; } ;
struct boot_catalog_entry {TYPE_1__ entry_data; int /*<<< orphan*/  entry_type; } ;
typedef  TYPE_2__ boot_catalog_section_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ET_BOOTABLE ; 
 int /*<<< orphan*/  ET_ENTRY_SE ; 
 int /*<<< orphan*/  cd9660_721 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_731 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct boot_catalog_entry* cd9660_init_boot_catalog_entry () ; 

__attribute__((used)) static struct boot_catalog_entry *
cd9660_boot_setup_section_entry(struct cd9660_boot_image *disk)
{
	struct boot_catalog_entry *entry;
	boot_catalog_section_entry *se;
	if ((entry = cd9660_init_boot_catalog_entry()) == NULL)
		return NULL;

	entry->entry_type = ET_ENTRY_SE;
	se = &entry->entry_data.SE;

	se->boot_indicator[0] = ET_BOOTABLE;
	se->media_type[0] = disk->targetMode;
	cd9660_721(disk->loadSegment, se->load_segment);
	cd9660_721(disk->num_sectors, se->sector_count);
	cd9660_731(disk->sector, se->load_rba);
	return entry;
}