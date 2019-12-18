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
struct device_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_link_put_kref (struct device_link*) ; 
 int /*<<< orphan*/  device_links_write_lock () ; 
 int /*<<< orphan*/  device_links_write_unlock () ; 
 int /*<<< orphan*/  device_pm_lock () ; 
 int /*<<< orphan*/  device_pm_unlock () ; 

void device_link_del(struct device_link *link)
{
	device_links_write_lock();
	device_pm_lock();
	device_link_put_kref(link);
	device_pm_unlock();
	device_links_write_unlock();
}