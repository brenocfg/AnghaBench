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
struct fsi_slave {int /*<<< orphan*/  id; int /*<<< orphan*/  link; struct fsi_master* master; } ;
struct fsi_master {int /*<<< orphan*/  (* term ) (struct fsi_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENODEV ; 
 int /*<<< orphan*/  stub1 (struct fsi_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsi_slave* to_fsi_slave (struct device*) ; 

__attribute__((used)) static ssize_t send_term_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct fsi_slave *slave = to_fsi_slave(dev);
	struct fsi_master *master = slave->master;

	if (!master->term)
		return -ENODEV;

	master->term(master, slave->link, slave->id);
	return count;
}