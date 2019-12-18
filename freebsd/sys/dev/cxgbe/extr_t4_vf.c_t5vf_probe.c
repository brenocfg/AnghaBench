#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {scalar_t__ device; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nitems (TYPE_1__*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 TYPE_1__* t5vf_pciids ; 

__attribute__((used)) static int
t5vf_probe(device_t dev)
{
	uint16_t d;
	size_t i;

	d = pci_get_device(dev);
	for (i = 0; i < nitems(t5vf_pciids); i++) {
		if (d == t5vf_pciids[i].device) {
			device_set_desc(dev, t5vf_pciids[i].desc);
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}