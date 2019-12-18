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
struct fsi_slave {unsigned long t_send_delay; unsigned long t_echo_delay; int /*<<< orphan*/  link; struct fsi_master* master; } ;
struct fsi_master {int /*<<< orphan*/  (* link_config ) (struct fsi_master*,int /*<<< orphan*/ ,unsigned long,unsigned long) ;} ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int fsi_slave_set_smode (struct fsi_slave*) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (struct fsi_master*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 struct fsi_slave* to_fsi_slave (struct device*) ; 

__attribute__((used)) static ssize_t slave_send_echo_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct fsi_slave *slave = to_fsi_slave(dev);
	struct fsi_master *master = slave->master;
	unsigned long val;
	int rc;

	if (kstrtoul(buf, 0, &val) < 0)
		return -EINVAL;

	if (val < 1 || val > 16)
		return -EINVAL;

	if (!master->link_config)
		return -ENXIO;

	/* Current HW mandates that send and echo delay are identical */
	slave->t_send_delay = val;
	slave->t_echo_delay = val;

	rc = fsi_slave_set_smode(slave);
	if (rc < 0)
		return rc;
	if (master->link_config)
		master->link_config(master, slave->link,
				    slave->t_send_delay,
				    slave->t_echo_delay);

	return count;
}