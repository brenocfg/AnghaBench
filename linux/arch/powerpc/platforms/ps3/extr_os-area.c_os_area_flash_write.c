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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (void const*,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_area_flash_mutex ; 
 TYPE_1__* os_area_flash_ops ; 
 int /*<<< orphan*/  stub1 (void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t os_area_flash_write(const void *buf, size_t count, loff_t pos)
{
	ssize_t res = -ENODEV;

	mutex_lock(&os_area_flash_mutex);
	if (os_area_flash_ops)
		res = os_area_flash_ops->write(buf, count, pos);
	mutex_unlock(&os_area_flash_mutex);

	return res;
}