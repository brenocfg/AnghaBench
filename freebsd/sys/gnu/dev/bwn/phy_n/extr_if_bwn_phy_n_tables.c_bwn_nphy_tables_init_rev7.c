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
struct TYPE_2__ {scalar_t__ phy_do_full_init; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NTAB_CHANEST_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_FRAMELT_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_FRAMESTRUCT_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_INTLEVEL_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_MCS_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_NOISEVAR_R7 ; 
 int /*<<< orphan*/  BWN_NTAB_PILOTLT_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_PILOT_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_TDI20A0_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_TDI20A1_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_TDI40A0_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_TDI40A1_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_TDTRN_R3 ; 
 int /*<<< orphan*/  BWN_NTAB_TMAP_R7 ; 
 int /*<<< orphan*/  bwn_nphy_tables_init_rev7_volatile (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tables_init_shared_lut (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_ntab_channelest_r3 ; 
 int /*<<< orphan*/  bwn_ntab_framelookup_r3 ; 
 int /*<<< orphan*/  bwn_ntab_framestruct_r3 ; 
 int /*<<< orphan*/  bwn_ntab_intlevel_r3 ; 
 int /*<<< orphan*/  bwn_ntab_mcs_r3 ; 
 int /*<<< orphan*/  bwn_ntab_noisevar_r7 ; 
 int /*<<< orphan*/  bwn_ntab_pilot_r3 ; 
 int /*<<< orphan*/  bwn_ntab_pilotlt_r3 ; 
 int /*<<< orphan*/  bwn_ntab_tdi20a0_r3 ; 
 int /*<<< orphan*/  bwn_ntab_tdi20a1_r3 ; 
 int /*<<< orphan*/  bwn_ntab_tdi40a0_r3 ; 
 int /*<<< orphan*/  bwn_ntab_tdi40a1_r3 ; 
 int /*<<< orphan*/  bwn_ntab_tdtrn_r3 ; 
 int /*<<< orphan*/  bwn_ntab_tmap_r7 ; 
 int /*<<< orphan*/  ntab_upload (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_nphy_tables_init_rev7(struct bwn_mac *mac)
{
	/* Static tables */
	if (mac->mac_phy.phy_do_full_init) {
		ntab_upload(mac, BWN_NTAB_FRAMESTRUCT_R3, bwn_ntab_framestruct_r3);
		ntab_upload(mac, BWN_NTAB_PILOT_R3, bwn_ntab_pilot_r3);
		ntab_upload(mac, BWN_NTAB_TMAP_R7, bwn_ntab_tmap_r7);
		ntab_upload(mac, BWN_NTAB_INTLEVEL_R3, bwn_ntab_intlevel_r3);
		ntab_upload(mac, BWN_NTAB_TDTRN_R3, bwn_ntab_tdtrn_r3);
		ntab_upload(mac, BWN_NTAB_NOISEVAR_R7, bwn_ntab_noisevar_r7);
		ntab_upload(mac, BWN_NTAB_MCS_R3, bwn_ntab_mcs_r3);
		ntab_upload(mac, BWN_NTAB_TDI20A0_R3, bwn_ntab_tdi20a0_r3);
		ntab_upload(mac, BWN_NTAB_TDI20A1_R3, bwn_ntab_tdi20a1_r3);
		ntab_upload(mac, BWN_NTAB_TDI40A0_R3, bwn_ntab_tdi40a0_r3);
		ntab_upload(mac, BWN_NTAB_TDI40A1_R3, bwn_ntab_tdi40a1_r3);
		ntab_upload(mac, BWN_NTAB_PILOTLT_R3, bwn_ntab_pilotlt_r3);
		ntab_upload(mac, BWN_NTAB_CHANEST_R3, bwn_ntab_channelest_r3);
		ntab_upload(mac, BWN_NTAB_FRAMELT_R3, bwn_ntab_framelookup_r3);
		bwn_nphy_tables_init_shared_lut(mac);
	}

	/* Volatile tables */
	bwn_nphy_tables_init_rev7_volatile(mac);
}