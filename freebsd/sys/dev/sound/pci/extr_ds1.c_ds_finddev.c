#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {scalar_t__ dev; scalar_t__ subdev; } ;

/* Variables and functions */
 TYPE_1__* ds_devs ; 

__attribute__((used)) static int
ds_finddev(u_int32_t dev, u_int32_t subdev)
{
	int i;

	for (i = 0; ds_devs[i].dev; i++) {
		if (ds_devs[i].dev == dev &&
		    (ds_devs[i].subdev == subdev || ds_devs[i].subdev == 0))
			return i;
	}
	return -1;
}