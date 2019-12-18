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
struct pcd_unit {int /*<<< orphan*/  info; } ;
struct gendisk {struct pcd_unit* private_data; } ;

/* Variables and functions */
 unsigned int cdrom_check_events (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static unsigned int pcd_block_check_events(struct gendisk *disk,
					   unsigned int clearing)
{
	struct pcd_unit *cd = disk->private_data;
	return cdrom_check_events(&cd->info, clearing);
}