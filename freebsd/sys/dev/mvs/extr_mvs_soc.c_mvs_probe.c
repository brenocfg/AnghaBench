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
struct TYPE_2__ {scalar_t__ id; scalar_t__ rev; char* name; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* mvs_ids ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  soc_id (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
mvs_probe(device_t dev)
{
	char buf[64];
	int i;
	uint32_t devid, revid;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "mrvl,sata"))
		return (ENXIO);

	soc_id(&devid, &revid);
	for (i = 0; mvs_ids[i].id != 0; i++) {
		if (mvs_ids[i].id == devid &&
		    mvs_ids[i].rev <= revid) {
			snprintf(buf, sizeof(buf), "%s SATA controller",
			    mvs_ids[i].name);
			device_set_desc_copy(dev, buf);
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}