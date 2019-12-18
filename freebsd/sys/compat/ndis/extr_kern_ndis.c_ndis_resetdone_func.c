#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ndis_softc {int /*<<< orphan*/  ndis_dev; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  ndis_status ;
struct TYPE_6__ {int /*<<< orphan*/  nmb_resetevent; TYPE_1__* nmb_physdeviceobj; } ;
typedef  TYPE_2__ ndis_miniport_block ;
typedef  TYPE_2__* ndis_handle ;
struct TYPE_5__ {int /*<<< orphan*/  do_devext; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IFF_DEBUG ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* NDISUSB_GET_IFNET (struct ndis_softc*) ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ndis_resetdone_func(ndis_handle adapter, ndis_status status,
	uint8_t addressingreset)
{
	ndis_miniport_block	*block;
	struct ndis_softc	*sc;
	struct ifnet		*ifp;

	block = adapter;
	sc = device_get_softc(block->nmb_physdeviceobj->do_devext);
	ifp = NDISUSB_GET_IFNET(sc);

	if (ifp && ifp->if_flags & IFF_DEBUG)
		device_printf(sc->ndis_dev, "reset done...\n");
	KeSetEvent(&block->nmb_resetevent, IO_NO_INCREMENT, FALSE);
}