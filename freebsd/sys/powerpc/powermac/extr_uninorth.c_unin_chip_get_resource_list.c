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
struct unin_chip_devinfo {struct resource_list udi_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct unin_chip_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
unin_chip_get_resource_list (device_t dev, device_t child)
{
	struct unin_chip_devinfo *dinfo;

	dinfo = device_get_ivars(child);
	return (&dinfo->udi_resources);
}