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
struct intel_raid_disk {int sectors; int sectors_hi; } ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static void
intel_set_disk_sectors(struct intel_raid_disk *disk, off_t sectors)
{

	disk->sectors = sectors & 0xffffffff;
	disk->sectors_hi = sectors >> 32;
}