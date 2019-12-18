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
struct sge_type {scalar_t__ sge_vid; scalar_t__ sge_did; int /*<<< orphan*/ * sge_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 struct sge_type* sge_devs ; 

__attribute__((used)) static int
sge_probe(device_t dev)
{
	struct sge_type *t;

	t = sge_devs;
	while (t->sge_name != NULL) {
		if ((pci_get_vendor(dev) == t->sge_vid) &&
		    (pci_get_device(dev) == t->sge_did)) {
			device_set_desc(dev, t->sge_name);
			return (BUS_PROBE_DEFAULT);
		}
		t++;
	}

	return (ENXIO);
}