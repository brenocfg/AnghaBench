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
struct ib_device_attr {int max_sge; } ;
struct ib_device {struct ib_device_attr attrs; } ;

/* Variables and functions */

__attribute__((used)) static int
sdp_get_max_dev_sge(struct ib_device *dev)
{
	struct ib_device_attr *device_attr;
	static int max_sges = -1;

	if (max_sges > 0)
		goto out;

	device_attr = &dev->attrs;
	max_sges = device_attr->max_sge;

out:
	return max_sges;
}