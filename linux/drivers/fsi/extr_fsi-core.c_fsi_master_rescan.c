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
struct fsi_master {int /*<<< orphan*/  scan_lock; } ;

/* Variables and functions */
 int fsi_master_scan (struct fsi_master*) ; 
 int /*<<< orphan*/  fsi_master_unscan (struct fsi_master*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int fsi_master_rescan(struct fsi_master *master)
{
	int rc;

	mutex_lock(&master->scan_lock);
	fsi_master_unscan(master);
	rc = fsi_master_scan(master);
	mutex_unlock(&master->scan_lock);

	return rc;
}