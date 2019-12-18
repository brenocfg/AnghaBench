#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ drm_pci_id_list_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_OBSOLETE (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ PCIC_DISPLAY ; 
 scalar_t__ PCIS_DISPLAY_OTHER ; 
 scalar_t__ PCIS_DISPLAY_VGA ; 
 int /*<<< orphan*/ * device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* drm_find_description (int,int,TYPE_1__ const*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

int
drm_probe_helper(device_t kdev, const drm_pci_id_list_t *idlist)
{
	const drm_pci_id_list_t *id_entry;
	int vendor, device;

	vendor = pci_get_vendor(kdev);
	device = pci_get_device(kdev);

	if (pci_get_class(kdev) != PCIC_DISPLAY ||
	    (pci_get_subclass(kdev) != PCIS_DISPLAY_VGA &&
	     pci_get_subclass(kdev) != PCIS_DISPLAY_OTHER))
		return (-ENXIO);

	id_entry = drm_find_description(vendor, device, idlist);
	if (id_entry != NULL) {
		if (device_get_desc(kdev) == NULL) {
			DRM_DEBUG("%s desc: %s\n",
			    device_get_nameunit(kdev), id_entry->name);
			device_set_desc(kdev, id_entry->name);
		}
		DRM_OBSOLETE(kdev);
		return (-BUS_PROBE_GENERIC);
	}

	return (-ENXIO);
}