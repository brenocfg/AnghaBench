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
typedef  scalar_t__ uint16_t ;
struct vmd_type {scalar_t__ vmd_vid; scalar_t__ vmd_did; int /*<<< orphan*/ * vmd_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 struct vmd_type* vmd_devs ; 

__attribute__((used)) static int
vmd_probe(device_t dev)
{
	struct vmd_type *t;
	uint16_t vid, did;

	t = vmd_devs;
	vid = pci_get_vendor(dev);
	did = pci_get_device(dev);

	while (t->vmd_name != NULL) {
		if (vid == t->vmd_vid &&
			did == t->vmd_did) {
			device_set_desc(dev, t->vmd_name);
			return (BUS_PROBE_DEFAULT);
		}
		t++;
	}

return (ENXIO);
}