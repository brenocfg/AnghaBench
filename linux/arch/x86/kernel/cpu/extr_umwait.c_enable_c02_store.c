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
typedef  int /*<<< orphan*/  u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umwait_control_cached ; 
 int umwait_ctrl_c02_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umwait_lock ; 
 int /*<<< orphan*/  umwait_update_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t enable_c02_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	bool c02_enable;
	u32 ctrl;
	int ret;

	ret = kstrtobool(buf, &c02_enable);
	if (ret)
		return ret;

	mutex_lock(&umwait_lock);

	ctrl = READ_ONCE(umwait_control_cached);
	if (c02_enable != umwait_ctrl_c02_enabled(ctrl))
		umwait_update_control(ctrl, c02_enable);

	mutex_unlock(&umwait_lock);

	return count;
}