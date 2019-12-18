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
 int /*<<< orphan*/  BWN_NTAB_BDI ; 
 int /*<<< orphan*/  BWN_NTAB_C0_ADJPLT ; 
 int /*<<< orphan*/  BWN_NTAB_C0_ESTPLT ; 
 int /*<<< orphan*/  BWN_NTAB_C0_GAINCTL ; 
 int /*<<< orphan*/  BWN_NTAB_C0_IQLT ; 
 int /*<<< orphan*/  BWN_NTAB_C0_LOFEEDTH ; 
 int /*<<< orphan*/  BWN_NTAB_C1_ADJPLT ; 
 int /*<<< orphan*/  BWN_NTAB_C1_ESTPLT ; 
 int /*<<< orphan*/  BWN_NTAB_C1_GAINCTL ; 
 int /*<<< orphan*/  BWN_NTAB_C1_IQLT ; 
 int /*<<< orphan*/  BWN_NTAB_C1_LOFEEDTH ; 
 int /*<<< orphan*/  BWN_NTAB_CHANEST ; 
 int /*<<< orphan*/  BWN_NTAB_FRAMELT ; 
 int /*<<< orphan*/  BWN_NTAB_FRAMESTRUCT ; 
 int /*<<< orphan*/  BWN_NTAB_INTLEVEL ; 
 int /*<<< orphan*/  BWN_NTAB_MCS ; 
 int /*<<< orphan*/  BWN_NTAB_NOISEVAR10 ; 
 int /*<<< orphan*/  BWN_NTAB_NOISEVAR11 ; 
 int /*<<< orphan*/  BWN_NTAB_PILOT ; 
 int /*<<< orphan*/  BWN_NTAB_PILOTLT ; 
 int /*<<< orphan*/  BWN_NTAB_TDI20A0 ; 
 int /*<<< orphan*/  BWN_NTAB_TDI20A1 ; 
 int /*<<< orphan*/  BWN_NTAB_TDI40A0 ; 
 int /*<<< orphan*/  BWN_NTAB_TDI40A1 ; 
 int /*<<< orphan*/  BWN_NTAB_TDTRN ; 
 int /*<<< orphan*/  BWN_NTAB_TMAP ; 
 int /*<<< orphan*/  bwn_ntab_adjustpower0 ; 
 int /*<<< orphan*/  bwn_ntab_adjustpower1 ; 
 int /*<<< orphan*/  bwn_ntab_bdi ; 
 int /*<<< orphan*/  bwn_ntab_channelest ; 
 int /*<<< orphan*/  bwn_ntab_estimatepowerlt0 ; 
 int /*<<< orphan*/  bwn_ntab_estimatepowerlt1 ; 
 int /*<<< orphan*/  bwn_ntab_framelookup ; 
 int /*<<< orphan*/  bwn_ntab_framestruct ; 
 int /*<<< orphan*/  bwn_ntab_gainctl0 ; 
 int /*<<< orphan*/  bwn_ntab_gainctl1 ; 
 int /*<<< orphan*/  bwn_ntab_intlevel ; 
 int /*<<< orphan*/  bwn_ntab_iqlt0 ; 
 int /*<<< orphan*/  bwn_ntab_iqlt1 ; 
 int /*<<< orphan*/  bwn_ntab_loftlt0 ; 
 int /*<<< orphan*/  bwn_ntab_loftlt1 ; 
 int /*<<< orphan*/  bwn_ntab_mcs ; 
 int /*<<< orphan*/  bwn_ntab_noisevar10 ; 
 int /*<<< orphan*/  bwn_ntab_noisevar11 ; 
 int /*<<< orphan*/  bwn_ntab_pilot ; 
 int /*<<< orphan*/  bwn_ntab_pilotlt ; 
 int /*<<< orphan*/  bwn_ntab_tdi20a0 ; 
 int /*<<< orphan*/  bwn_ntab_tdi20a1 ; 
 int /*<<< orphan*/  bwn_ntab_tdi40a0 ; 
 int /*<<< orphan*/  bwn_ntab_tdi40a1 ; 
 int /*<<< orphan*/  bwn_ntab_tdtrn ; 
 int /*<<< orphan*/  bwn_ntab_tmap ; 
 int /*<<< orphan*/  ntab_upload (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_nphy_tables_init_rev0(struct bwn_mac *mac)
{
	/* Static tables */
	if (mac->mac_phy.phy_do_full_init) {
		ntab_upload(mac, BWN_NTAB_FRAMESTRUCT, bwn_ntab_framestruct);
		ntab_upload(mac, BWN_NTAB_FRAMELT, bwn_ntab_framelookup);
		ntab_upload(mac, BWN_NTAB_TMAP, bwn_ntab_tmap);
		ntab_upload(mac, BWN_NTAB_TDTRN, bwn_ntab_tdtrn);
		ntab_upload(mac, BWN_NTAB_INTLEVEL, bwn_ntab_intlevel);
		ntab_upload(mac, BWN_NTAB_PILOT, bwn_ntab_pilot);
		ntab_upload(mac, BWN_NTAB_TDI20A0, bwn_ntab_tdi20a0);
		ntab_upload(mac, BWN_NTAB_TDI20A1, bwn_ntab_tdi20a1);
		ntab_upload(mac, BWN_NTAB_TDI40A0, bwn_ntab_tdi40a0);
		ntab_upload(mac, BWN_NTAB_TDI40A1, bwn_ntab_tdi40a1);
		ntab_upload(mac, BWN_NTAB_CHANEST, bwn_ntab_channelest);
		ntab_upload(mac, BWN_NTAB_MCS, bwn_ntab_mcs);
		ntab_upload(mac, BWN_NTAB_NOISEVAR10, bwn_ntab_noisevar10);
		ntab_upload(mac, BWN_NTAB_NOISEVAR11, bwn_ntab_noisevar11);
	}

	/* Volatile tables */
	ntab_upload(mac, BWN_NTAB_BDI, bwn_ntab_bdi);
	ntab_upload(mac, BWN_NTAB_PILOTLT, bwn_ntab_pilotlt);
	ntab_upload(mac, BWN_NTAB_C0_GAINCTL, bwn_ntab_gainctl0);
	ntab_upload(mac, BWN_NTAB_C1_GAINCTL, bwn_ntab_gainctl1);
	ntab_upload(mac, BWN_NTAB_C0_ESTPLT, bwn_ntab_estimatepowerlt0);
	ntab_upload(mac, BWN_NTAB_C1_ESTPLT, bwn_ntab_estimatepowerlt1);
	ntab_upload(mac, BWN_NTAB_C0_ADJPLT, bwn_ntab_adjustpower0);
	ntab_upload(mac, BWN_NTAB_C1_ADJPLT, bwn_ntab_adjustpower1);
	ntab_upload(mac, BWN_NTAB_C0_IQLT, bwn_ntab_iqlt0);
	ntab_upload(mac, BWN_NTAB_C1_IQLT, bwn_ntab_iqlt1);
	ntab_upload(mac, BWN_NTAB_C0_LOFEEDTH, bwn_ntab_loftlt0);
	ntab_upload(mac, BWN_NTAB_C1_LOFEEDTH, bwn_ntab_loftlt1);
}