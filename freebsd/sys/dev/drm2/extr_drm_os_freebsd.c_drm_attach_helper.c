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
struct drm_driver {int dummy; } ;
struct drm_device {int /*<<< orphan*/  id_entry; } ;
typedef  int /*<<< orphan*/  drm_pci_id_list_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct drm_device* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_find_description (int,int,int /*<<< orphan*/  const*) ; 
 int drm_get_pci_dev (int /*<<< orphan*/ ,struct drm_device*,struct drm_driver*) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

int
drm_attach_helper(device_t kdev, const drm_pci_id_list_t *idlist,
    struct drm_driver *driver)
{
	struct drm_device *dev;
	int vendor, device;
	int ret;

	dev = device_get_softc(kdev);

	vendor = pci_get_vendor(kdev);
	device = pci_get_device(kdev);
	dev->id_entry = drm_find_description(vendor, device, idlist);

	ret = drm_get_pci_dev(kdev, dev, driver);

	return (ret);
}