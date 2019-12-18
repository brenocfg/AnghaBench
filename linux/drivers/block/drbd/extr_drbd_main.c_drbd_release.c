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
struct gendisk {struct drbd_device* private_data; } ;
struct drbd_device {int /*<<< orphan*/  open_cnt; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_main_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_release(struct gendisk *gd, fmode_t mode)
{
	struct drbd_device *device = gd->private_data;
	mutex_lock(&drbd_main_mutex);
	device->open_cnt--;
	mutex_unlock(&drbd_main_mutex);
}