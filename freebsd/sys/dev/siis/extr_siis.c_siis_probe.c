#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ id; char* name; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 TYPE_1__* siis_ids ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
siis_probe(device_t dev)
{
	char buf[64];
	int i;
	uint32_t devid = pci_get_devid(dev);

	for (i = 0; siis_ids[i].id != 0; i++) {
		if (siis_ids[i].id == devid) {
			snprintf(buf, sizeof(buf), "%s SATA controller",
			    siis_ids[i].name);
			device_set_desc_copy(dev, buf);
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}