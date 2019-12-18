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
struct ndis_softc {int ndis_am_rid; int /*<<< orphan*/  ndis_dev; int /*<<< orphan*/ * ndis_res_am; int /*<<< orphan*/  ndis_rl; int /*<<< orphan*/  ndis_rescnt; } ;

/* Variables and functions */
 int CARD_SET_MEMORY_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CARD_SET_RES_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int NDIS_AM_RID ; 
 int /*<<< orphan*/  PCCARD_A_MEM_ATTR ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ndis_alloc_amem(struct ndis_softc *sc)
{
	int error, rid;

	rid = NDIS_AM_RID;
	sc->ndis_res_am = bus_alloc_resource_anywhere(sc->ndis_dev,
	    SYS_RES_MEMORY, &rid, 0x1000, RF_ACTIVE);

	if (sc->ndis_res_am == NULL) {
		device_printf(sc->ndis_dev,
		    "failed to allocate attribute memory\n");
		return(ENXIO);
	}
	sc->ndis_rescnt++;
	resource_list_add(&sc->ndis_rl, SYS_RES_MEMORY, rid,
	    rman_get_start(sc->ndis_res_am), rman_get_end(sc->ndis_res_am),
	    rman_get_size(sc->ndis_res_am));

	error = CARD_SET_MEMORY_OFFSET(device_get_parent(sc->ndis_dev),
	    sc->ndis_dev, rid, 0, NULL);

	if (error) {
		device_printf(sc->ndis_dev,
		    "CARD_SET_MEMORY_OFFSET() returned 0x%x\n", error);
		return(error);
	}

	error = CARD_SET_RES_FLAGS(device_get_parent(sc->ndis_dev),
	    sc->ndis_dev, SYS_RES_MEMORY, rid, PCCARD_A_MEM_ATTR);

	if (error) {
		device_printf(sc->ndis_dev,
		    "CARD_SET_RES_FLAGS() returned 0x%x\n", error);
		return(error);
	}

	sc->ndis_am_rid = rid;

	return(0);
}