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
struct edac_device_ctl_info {int nr_instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  _octeon_l2c_poll_oct2 (struct edac_device_ctl_info*,int) ; 

__attribute__((used)) static void octeon_l2c_poll_oct2(struct edac_device_ctl_info *l2c)
{
	int i;
	for (i = 0; i < l2c->nr_instances; i++)
		_octeon_l2c_poll_oct2(l2c, i);
}