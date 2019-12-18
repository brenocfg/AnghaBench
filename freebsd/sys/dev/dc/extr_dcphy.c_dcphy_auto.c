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
struct mii_softc {int mii_capabilities; TYPE_1__* mii_pdata; } ;
struct dc_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mii_ifp; } ;

/* Variables and functions */
 int BMSR_100TXHDX ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_10BTCTRL ; 
 int /*<<< orphan*/  DC_10BTSTAT ; 
 int /*<<< orphan*/  DC_ASTAT_TXDISABLE ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int /*<<< orphan*/  DC_NETCFG_FULLDUPLEX ; 
 int /*<<< orphan*/  DC_NETCFG_PORTSEL ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SIARESET ; 
 int /*<<< orphan*/  DC_SIA_RESET ; 
 int /*<<< orphan*/  DC_TCTL_AUTONEGENBL ; 
 int EJUSTRETURN ; 
 struct dc_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dcphy_auto(struct mii_softc *mii)
{
	struct dc_softc		*sc;

	sc = if_getsoftc(mii->mii_pdata->mii_ifp);

	DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_PORTSEL);
	DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_FULLDUPLEX);
	DC_CLRBIT(sc, DC_SIARESET, DC_SIA_RESET);
	if (mii->mii_capabilities & BMSR_100TXHDX)
		CSR_WRITE_4(sc, DC_10BTCTRL, 0x3FFFF);
	else
		CSR_WRITE_4(sc, DC_10BTCTRL, 0xFFFF);
	DC_SETBIT(sc, DC_SIARESET, DC_SIA_RESET);
	DC_SETBIT(sc, DC_10BTCTRL, DC_TCTL_AUTONEGENBL);
	DC_SETBIT(sc, DC_10BTSTAT, DC_ASTAT_TXDISABLE);

	return (EJUSTRETURN);
}