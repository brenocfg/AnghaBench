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
struct viawd_device {scalar_t__ device; int /*<<< orphan*/ * desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ VENDORID_VIA ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 struct viawd_device* viawd_devices ; 

__attribute__((used)) static struct viawd_device *
viawd_find(device_t dev)
{
	struct viawd_device *id;

	if (pci_get_vendor(dev) != VENDORID_VIA)
		return (NULL);
	for (id = viawd_devices; id->desc != NULL; id++)
		if (pci_get_device(dev) == id->device)
			return (id);
	return (NULL);
}