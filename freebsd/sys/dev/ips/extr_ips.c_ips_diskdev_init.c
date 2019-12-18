#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * diskdev; TYPE_1__* drives; } ;
typedef  TYPE_2__ ips_softc_t ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  sector_count; int /*<<< orphan*/  raid_lvl; } ;

/* Variables and functions */
 scalar_t__ IPS_LD_DEGRADED ; 
 scalar_t__ IPS_LD_FREE ; 
 scalar_t__ IPS_LD_OKAY ; 
 int IPS_MAX_NUM_DRIVES ; 
 scalar_t__ bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ips_diskdev_statename (scalar_t__) ; 

__attribute__((used)) static int ips_diskdev_init(ips_softc_t *sc)
{
	int i;
	for(i=0; i < IPS_MAX_NUM_DRIVES; i++){
		if(sc->drives[i].state == IPS_LD_FREE) continue;
		device_printf(sc->dev, "Logical Drive %d: RAID%d sectors: %u, state %s\n",
			i, sc->drives[i].raid_lvl,
			sc->drives[i].sector_count,
			ips_diskdev_statename(sc->drives[i].state));
		if(sc->drives[i].state == IPS_LD_OKAY ||
		   sc->drives[i].state == IPS_LD_DEGRADED){
			sc->diskdev[i] = device_add_child(sc->dev, NULL, -1);
			device_set_ivars(sc->diskdev[i],(void *)(uintptr_t) i);
		}
	}
	if(bus_generic_attach(sc->dev)){
		device_printf(sc->dev, "Attaching bus failed\n");
	}
	return 0;
}