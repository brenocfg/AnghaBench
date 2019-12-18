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
typedef  scalar_t__ u64 ;
struct drbd_device {scalar_t__ ed_uuid; } ;

/* Variables and functions */

__attribute__((used)) static inline int drbd_set_ed_uuid(struct drbd_device *device, u64 val)
{
	int changed = device->ed_uuid != val;
	device->ed_uuid = val;
	return changed;
}