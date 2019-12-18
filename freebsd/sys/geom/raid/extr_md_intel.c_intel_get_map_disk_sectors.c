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
struct intel_raid_map {scalar_t__ disk_sectors; scalar_t__ disk_sectors_hi; } ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static off_t
intel_get_map_disk_sectors(struct intel_raid_map *mmap)
{
	off_t disk_sectors = (off_t)mmap->disk_sectors_hi << 32;

	disk_sectors += mmap->disk_sectors;
	return (disk_sectors);
}