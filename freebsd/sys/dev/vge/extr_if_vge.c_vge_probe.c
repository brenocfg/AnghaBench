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
struct vge_type {scalar_t__ vge_vid; scalar_t__ vge_did; int /*<<< orphan*/ * vge_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 struct vge_type* vge_devs ; 

__attribute__((used)) static int
vge_probe(device_t dev)
{
	struct vge_type	*t;

	t = vge_devs;

	while (t->vge_name != NULL) {
		if ((pci_get_vendor(dev) == t->vge_vid) &&
		    (pci_get_device(dev) == t->vge_did)) {
			device_set_desc(dev, t->vge_name);
			return (BUS_PROBE_DEFAULT);
		}
		t++;
	}

	return (ENXIO);
}