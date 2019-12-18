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
typedef  int uint16_t ;
typedef  int u_int ;
struct imx_wdog_softc {int sc_timeout; int sc_pde_enabled; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int EINVAL ; 
 int RD2 (struct imx_wdog_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDOG_CR_REG ; 
 int WDOG_CR_WDE ; 
 int WDOG_CR_WT_MASK ; 
 int WDOG_CR_WT_SHIFT ; 
 int WDOG_MCR_PDE ; 
 int /*<<< orphan*/  WDOG_MCR_REG ; 
 int /*<<< orphan*/  WDOG_SR_REG ; 
 int WDOG_SR_STEP1 ; 
 int WDOG_SR_STEP2 ; 
 int /*<<< orphan*/  WR2 (struct imx_wdog_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imx_wdog_enable(struct imx_wdog_softc *sc, u_int timeout)
{
	uint16_t reg;

	if (timeout < 1 || timeout > 128)
		return (EINVAL);

	mtx_lock(&sc->sc_mtx);
	if (timeout != sc->sc_timeout) {
		sc->sc_timeout = timeout;
		reg = RD2(sc, WDOG_CR_REG);
		reg &= ~WDOG_CR_WT_MASK;
		reg |= ((2 * timeout - 1) << WDOG_CR_WT_SHIFT);
		WR2(sc, WDOG_CR_REG, reg | WDOG_CR_WDE);
	}
	/* Refresh counter */
	WR2(sc, WDOG_SR_REG, WDOG_SR_STEP1);
	WR2(sc, WDOG_SR_REG, WDOG_SR_STEP2);
	/* Watchdog active, can disable rom-boot watchdog. */
	if (sc->sc_pde_enabled) {
		sc->sc_pde_enabled = false;
		reg = RD2(sc, WDOG_MCR_REG);
		WR2(sc, WDOG_MCR_REG, reg & ~WDOG_MCR_PDE);
	}
	mtx_unlock(&sc->sc_mtx);

	return (0);
}