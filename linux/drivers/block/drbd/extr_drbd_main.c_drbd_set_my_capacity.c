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
struct drbd_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  _drbd_set_my_capacity (struct drbd_device*,int) ; 
 int /*<<< orphan*/  drbd_info (struct drbd_device*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ppsize (char*,int) ; 

void drbd_set_my_capacity(struct drbd_device *device, sector_t size)
{
	char ppb[10];
	_drbd_set_my_capacity(device, size);
	drbd_info(device, "size = %s (%llu KB)\n",
		ppsize(ppb, size>>1), (unsigned long long)size>>1);
}