#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ciss_device_address {int dummy; } ciss_device_address ;
typedef  scalar_t__ u_int32_t ;
struct ciss_softc {TYPE_3__** ciss_physical; } ;
struct ciss_lun_report {TYPE_2__* lun; int /*<<< orphan*/  list_size; } ;
struct TYPE_4__ {scalar_t__ extra_address; scalar_t__ mode; } ;
struct TYPE_5__ {TYPE_1__ physical; } ;
struct TYPE_6__ {int cp_online; TYPE_2__ cp_address; } ;

/* Variables and functions */
 int CISS_EXTRA_BUS2 (scalar_t__) ; 
 scalar_t__ CISS_EXTRA_BUS3 (scalar_t__) ; 
 int CISS_EXTRA_MODE2 (scalar_t__) ; 
 int CISS_EXTRA_TARGET2 (scalar_t__) ; 
 scalar_t__ CISS_EXTRA_TARGET3 (scalar_t__) ; 
 scalar_t__ CISS_HDR_ADDRESS_MODE_MASK_PERIPHERAL ; 
 scalar_t__ ciss_expose_hidden_physical ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ciss_filter_physical(struct ciss_softc *sc, struct ciss_lun_report *cll)
{
    u_int32_t ea;
    int i, nphys;
    int	bus, target;

    nphys = (ntohl(cll->list_size) / sizeof(union ciss_device_address));
    for (i = 0; i < nphys; i++) {
	if (cll->lun[i].physical.extra_address == 0)
	    continue;

	/*
	 * Filter out devices that we don't want.  Level 3 LUNs could
	 * probably be supported, but the docs don't give enough of a
	 * hint to know how.
	 *
	 * The mode field of the physical address is likely set to have
	 * hard disks masked out.  Honor it unless the user has overridden
	 * us with the tunable.  We also munge the inquiry data for these
	 * disks so that they only show up as passthrough devices.  Keeping
	 * them visible in this fashion is useful for doing things like
	 * flashing firmware.
	 */
	ea = cll->lun[i].physical.extra_address;
	if ((CISS_EXTRA_BUS3(ea) != 0) || (CISS_EXTRA_TARGET3(ea) != 0) ||
	    (CISS_EXTRA_MODE2(ea) == 0x3))
	    continue;
	if ((ciss_expose_hidden_physical == 0) &&
	   (cll->lun[i].physical.mode == CISS_HDR_ADDRESS_MODE_MASK_PERIPHERAL))
	    continue;

	/*
	 * Note: CISS firmware numbers physical busses starting at '1', not
	 *       '0'.  This numbering is internal to the firmware and is only
	 *       used as a hint here.
	 */
	bus = CISS_EXTRA_BUS2(ea) - 1;
	target = CISS_EXTRA_TARGET2(ea);
	sc->ciss_physical[bus][target].cp_address = cll->lun[i];
	sc->ciss_physical[bus][target].cp_online = 1;
    }

    return (0);
}