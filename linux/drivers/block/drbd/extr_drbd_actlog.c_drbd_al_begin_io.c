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
struct drbd_interval {int dummy; } ;
struct drbd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_al_begin_io_commit (struct drbd_device*) ; 
 scalar_t__ drbd_al_begin_io_prepare (struct drbd_device*,struct drbd_interval*) ; 

void drbd_al_begin_io(struct drbd_device *device, struct drbd_interval *i)
{
	if (drbd_al_begin_io_prepare(device, i))
		drbd_al_begin_io_commit(device);
}