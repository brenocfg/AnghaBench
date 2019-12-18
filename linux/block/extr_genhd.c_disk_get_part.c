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
struct hd_struct {int dummy; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 struct hd_struct* __disk_get_part (struct gendisk*,int) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_to_dev (struct hd_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct hd_struct *disk_get_part(struct gendisk *disk, int partno)
{
	struct hd_struct *part;

	rcu_read_lock();
	part = __disk_get_part(disk, partno);
	if (part)
		get_device(part_to_dev(part));
	rcu_read_unlock();

	return part;
}