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
struct drbd_device {TYPE_1__* resource; } ;
typedef  enum drbd_force_detach_flags { ____Placeholder_drbd_force_detach_flags } drbd_force_detach_flags ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drbd_chk_io_error_ (struct drbd_device*,int,char const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void drbd_chk_io_error_(struct drbd_device *device,
	int error, enum drbd_force_detach_flags forcedetach, const char *where)
{
	if (error) {
		unsigned long flags;
		spin_lock_irqsave(&device->resource->req_lock, flags);
		__drbd_chk_io_error_(device, forcedetach, where);
		spin_unlock_irqrestore(&device->resource->req_lock, flags);
	}
}