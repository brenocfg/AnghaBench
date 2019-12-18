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
struct simdisk {scalar_t__ queue; scalar_t__ gd; } ;
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  del_gendisk (scalar_t__) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  simdisk_detach (struct simdisk*) ; 

__attribute__((used)) static void simdisk_teardown(struct simdisk *dev, int which,
		struct proc_dir_entry *procdir)
{
	char tmp[2] = { '0' + which, 0 };

	simdisk_detach(dev);
	if (dev->gd)
		del_gendisk(dev->gd);
	if (dev->queue)
		blk_cleanup_queue(dev->queue);
	remove_proc_entry(tmp, procdir);
}