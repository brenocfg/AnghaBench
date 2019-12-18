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
struct mii_softc {struct mii_data* mii_pdata; } ;
struct mii_data {int /*<<< orphan*/  mii_media_active; int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_ifp; } ;
struct dc_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_ISR ; 
 int DC_ISR_LINKFAIL ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int DC_NETCFG_FULLDUPLEX ; 
 int DC_NETCFG_SPEEDSEL ; 
 int /*<<< orphan*/  IFM_100_TX ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 struct dc_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pnphy_status(struct mii_softc *sc)
{
	struct mii_data *mii = sc->mii_pdata;
	int reg;
	struct dc_softc		*dc_sc;

	dc_sc = if_getsoftc(mii->mii_ifp);

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	reg = CSR_READ_4(dc_sc, DC_ISR);
	if (!(reg & DC_ISR_LINKFAIL))
		mii->mii_media_status |= IFM_ACTIVE;
	reg = CSR_READ_4(dc_sc, DC_NETCFG);
	if (reg & DC_NETCFG_SPEEDSEL)
		mii->mii_media_active |= IFM_10_T;
	else
		mii->mii_media_active |= IFM_100_TX;
	if (reg & DC_NETCFG_FULLDUPLEX)
		mii->mii_media_active |= IFM_FDX;
	else
		mii->mii_media_active |= IFM_HDX;
}