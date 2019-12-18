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
struct vpe {unsigned long ntcs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long aprp_cpu_index () ; 
 struct vpe* get_vpe (unsigned long) ; 
 unsigned long hw_tcs ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t ntcs_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t len)
{
	struct vpe *vpe = get_vpe(aprp_cpu_index());
	unsigned long new;
	int ret;

	ret = kstrtoul(buf, 0, &new);
	if (ret < 0)
		return ret;

	if (new == 0 || new > (hw_tcs - aprp_cpu_index()))
		return -EINVAL;

	vpe->ntcs = new;

	return len;
}