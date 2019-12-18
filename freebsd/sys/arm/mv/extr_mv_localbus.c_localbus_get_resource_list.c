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
struct resource_list {int dummy; } ;
struct localbus_devinfo {struct resource_list di_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct localbus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
localbus_get_resource_list(device_t bus, device_t child)
{
	struct localbus_devinfo *di;

	di = device_get_ivars(child);
	return (&di->di_res);
}