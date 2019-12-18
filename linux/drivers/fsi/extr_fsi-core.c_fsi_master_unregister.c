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
struct fsi_master {int idx; int /*<<< orphan*/  dev; int /*<<< orphan*/  scan_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsi_master_unscan (struct fsi_master*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  master_ida ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fsi_master_unregister(struct fsi_master *master)
{
	if (master->idx >= 0) {
		ida_simple_remove(&master_ida, master->idx);
		master->idx = -1;
	}

	mutex_lock(&master->scan_lock);
	fsi_master_unscan(master);
	mutex_unlock(&master->scan_lock);
	device_unregister(&master->dev);
}