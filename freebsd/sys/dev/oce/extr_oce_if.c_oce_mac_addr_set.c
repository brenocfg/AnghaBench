#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  size_of_struct; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; TYPE_1__ macaddr; int /*<<< orphan*/  ifp; int /*<<< orphan*/  if_id; int /*<<< orphan*/  pmac_id; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IF_LLADDR (int /*<<< orphan*/ ) ; 
 int bcmp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int oce_mbox_macaddr_add (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int oce_mbox_macaddr_del (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oce_mac_addr_set(POCE_SOFTC sc)
{
	uint32_t old_pmac_id = sc->pmac_id;
	int status = 0;

	
	status = bcmp((IF_LLADDR(sc->ifp)), sc->macaddr.mac_addr,
			 sc->macaddr.size_of_struct);
	if (!status)
		return;

	status = oce_mbox_macaddr_add(sc, (uint8_t *)(IF_LLADDR(sc->ifp)),
					sc->if_id, &sc->pmac_id);
	if (!status) {
		status = oce_mbox_macaddr_del(sc, sc->if_id, old_pmac_id);
		bcopy((IF_LLADDR(sc->ifp)), sc->macaddr.mac_addr,
				 sc->macaddr.size_of_struct); 
	}
	if (status)
		device_printf(sc->dev, "Failed update macaddress\n");

}