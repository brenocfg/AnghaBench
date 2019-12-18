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
typedef  int uint32_t ;
struct et_softc {int sc_flags; TYPE_1__* ifp; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int EM_PM_GIGEPHY_ENB ; 
 int ET_FLAG_FASTETHER ; 
 int /*<<< orphan*/  ET_LOCK (struct et_softc*) ; 
 int /*<<< orphan*/  ET_PM ; 
 int ET_PM_RXCLK_GATE ; 
 int ET_PM_SYSCLK_GATE ; 
 int ET_PM_TXCLK_GATE ; 
 int /*<<< orphan*/  ET_UNLOCK (struct et_softc*) ; 
 int IFF_UP ; 
 struct et_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et_init_locked (struct et_softc*) ; 

__attribute__((used)) static int
et_resume(device_t dev)
{
	struct et_softc *sc;
	uint32_t pmcfg;

	sc = device_get_softc(dev);
	ET_LOCK(sc);
	/* Take PHY out of COMA and enable clocks. */
	pmcfg = ET_PM_SYSCLK_GATE | ET_PM_TXCLK_GATE | ET_PM_RXCLK_GATE;
	if ((sc->sc_flags & ET_FLAG_FASTETHER) == 0)
		pmcfg |= EM_PM_GIGEPHY_ENB;
	CSR_WRITE_4(sc, ET_PM, pmcfg);
	if ((sc->ifp->if_flags & IFF_UP) != 0)
		et_init_locked(sc);
	ET_UNLOCK(sc);
	return (0);
}