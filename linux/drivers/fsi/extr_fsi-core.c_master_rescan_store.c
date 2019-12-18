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
struct fsi_master {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int fsi_master_rescan (struct fsi_master*) ; 
 struct fsi_master* to_fsi_master (struct device*) ; 

__attribute__((used)) static ssize_t master_rescan_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct fsi_master *master = to_fsi_master(dev);
	int rc;

	rc = fsi_master_rescan(master);
	if (rc < 0)
		return rc;

	return count;
}