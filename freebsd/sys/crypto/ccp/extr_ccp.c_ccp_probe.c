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
typedef  scalar_t__ uint32_t ;
struct pciid {scalar_t__ devid; int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct pciid* ccp_ids ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nitems (struct pciid*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccp_probe(device_t dev)
{
	struct pciid *ip;
	uint32_t id;

	id = pci_get_devid(dev);
	for (ip = ccp_ids; ip < &ccp_ids[nitems(ccp_ids)]; ip++) {
		if (id == ip->devid) {
			device_set_desc(dev, ip->desc);
			return (0);
		}
	}
	return (ENXIO);
}