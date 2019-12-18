#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int arp_filter; int dhcp_client_filt; int dhcp_server_filt; int net_bios_filt; int bcast_filt; int ipv6_nbr_filt; int ipv6_ra_filt; int ipv6_ras_filt; int mcast_filt; scalar_t__ mgmt_enable; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct oce_async_evt_grp5_os2bmc {TYPE_2__ u; } ;
struct TYPE_7__ {int bmc_filt_mask; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  DW_SWAP (struct oce_async_evt_grp5_os2bmc*,int) ; 
 int /*<<< orphan*/  OCE_FLAGS_OS2BMC ; 

__attribute__((used)) static void oce_async_grp5_osbmc_process(POCE_SOFTC sc,
					 struct oce_async_evt_grp5_os2bmc *evt)
{
	DW_SWAP(evt, sizeof(struct oce_async_evt_grp5_os2bmc));
	if (evt->u.s.mgmt_enable)
		sc->flags |= OCE_FLAGS_OS2BMC;
	else
		return;

	sc->bmc_filt_mask = evt->u.s.arp_filter;
	sc->bmc_filt_mask |= (evt->u.s.dhcp_client_filt << 1);
	sc->bmc_filt_mask |= (evt->u.s.dhcp_server_filt << 2);
	sc->bmc_filt_mask |= (evt->u.s.net_bios_filt << 3);
	sc->bmc_filt_mask |= (evt->u.s.bcast_filt << 4);
	sc->bmc_filt_mask |= (evt->u.s.ipv6_nbr_filt << 5);
	sc->bmc_filt_mask |= (evt->u.s.ipv6_ra_filt << 6);
	sc->bmc_filt_mask |= (evt->u.s.ipv6_ras_filt << 7);
	sc->bmc_filt_mask |= (evt->u.s.mcast_filt << 8);
}