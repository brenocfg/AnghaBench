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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  umwait_control_cached ; 
 int umwait_ctrl_max_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
max_time_show(struct device *kobj, struct device_attribute *attr, char *buf)
{
	u32 ctrl = READ_ONCE(umwait_control_cached);

	return sprintf(buf, "%u\n", umwait_ctrl_max_time(ctrl));
}