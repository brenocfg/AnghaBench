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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int MSR_IA32_UMWAIT_CONTROL_TIME_MASK ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umwait_control_cached ; 
 int /*<<< orphan*/  umwait_ctrl_c02_enabled (int) ; 
 int umwait_ctrl_max_time (int) ; 
 int /*<<< orphan*/  umwait_lock ; 
 int /*<<< orphan*/  umwait_update_control (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t max_time_store(struct device *kobj,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	u32 max_time, ctrl;
	int ret;

	ret = kstrtou32(buf, 0, &max_time);
	if (ret)
		return ret;

	/* bits[1:0] must be zero */
	if (max_time & ~MSR_IA32_UMWAIT_CONTROL_TIME_MASK)
		return -EINVAL;

	mutex_lock(&umwait_lock);

	ctrl = READ_ONCE(umwait_control_cached);
	if (max_time != umwait_ctrl_max_time(ctrl))
		umwait_update_control(max_time, umwait_ctrl_c02_enabled(ctrl));

	mutex_unlock(&umwait_lock);

	return count;
}