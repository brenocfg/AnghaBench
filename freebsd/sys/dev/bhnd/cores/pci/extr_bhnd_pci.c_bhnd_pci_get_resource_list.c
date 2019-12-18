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
struct bhnd_pci_devinfo {struct resource_list resources; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 struct bhnd_pci_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 

__attribute__((used)) static struct resource_list *
bhnd_pci_get_resource_list(device_t dev, device_t child)
{
	struct bhnd_pci_devinfo *dinfo;

	if (device_get_parent(child) != dev)
		return (NULL);

	dinfo = device_get_ivars(child);
	return (&dinfo->resources);
}