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
typedef  int /*<<< orphan*/  u_int32_t ;
struct hme_softc {scalar_t__* sc_phys; TYPE_3__* sc_mii; } ;
struct TYPE_5__ {TYPE_1__* ifm_cur; } ;
struct TYPE_6__ {TYPE_2__ mii_media; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  HME_MACI_XIF ; 
 int /*<<< orphan*/  HME_MAC_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_MAC_WRITE_4 (struct hme_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_MAC_XIF_MIIENABLE ; 
 int /*<<< orphan*/  HME_MIFI_CFG ; 
 int /*<<< orphan*/  HME_MIF_WRITE_4 (struct hme_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HME_PHYAD_EXTERNAL ; 
 size_t IFM_INST (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hme_mifinit(struct hme_softc *sc)
{
	u_int32_t v;

	/*
	 * Configure the MIF in frame mode, polling disabled, internal PHY
	 * selected.
	 */
	HME_MIF_WRITE_4(sc, HME_MIFI_CFG, 0);

	/*
	 * If the currently selected media uses the external transceiver,
	 * enable its MII drivers (which basically isolates the internal
	 * one and vice versa). In case the current media hasn't been set,
	 * yet, we default to the internal transceiver.
	 */
	v = HME_MAC_READ_4(sc, HME_MACI_XIF);
	if (sc->sc_mii != NULL && sc->sc_mii->mii_media.ifm_cur != NULL &&
	    sc->sc_phys[IFM_INST(sc->sc_mii->mii_media.ifm_cur->ifm_media)] ==
	    HME_PHYAD_EXTERNAL)
		v |= HME_MAC_XIF_MIIENABLE;
	else
		v &= ~HME_MAC_XIF_MIIENABLE;
	HME_MAC_WRITE_4(sc, HME_MACI_XIF, v);
}