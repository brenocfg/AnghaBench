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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int allow_tsx_force_abort ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 size_t kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  update_tfa_sched ; 

__attribute__((used)) static ssize_t set_sysctl_tfa(struct device *cdev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	bool val;
	ssize_t ret;

	ret = kstrtobool(buf, &val);
	if (ret)
		return ret;

	/* no change */
	if (val == allow_tsx_force_abort)
		return count;

	allow_tsx_force_abort = val;

	get_online_cpus();
	on_each_cpu(update_tfa_sched, NULL, 1);
	put_online_cpus();

	return count;
}