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
struct mii_softc {TYPE_1__* mii_pdata; } ;
struct dc_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mii_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SIARESET ; 
 int /*<<< orphan*/  DC_SIA_RESET ; 
 int /*<<< orphan*/  DELAY (int) ; 
 struct dc_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dcphy_reset(struct mii_softc *mii)
{
	struct dc_softc		*sc;

	sc = if_getsoftc(mii->mii_pdata->mii_ifp);

	DC_CLRBIT(sc, DC_SIARESET, DC_SIA_RESET);
	DELAY(1000);
	DC_SETBIT(sc, DC_SIARESET, DC_SIA_RESET);
}