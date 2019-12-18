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
struct gendisk {scalar_t__ ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __disk_unblock_events (struct gendisk*,int) ; 

void disk_unblock_events(struct gendisk *disk)
{
	if (disk->ev)
		__disk_unblock_events(disk, false);
}