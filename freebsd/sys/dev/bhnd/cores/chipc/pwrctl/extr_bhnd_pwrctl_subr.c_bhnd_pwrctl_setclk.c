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
typedef  int uint32_t ;
struct bhnd_pwrctl_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  chipc_dev; } ;
typedef  int bhnd_clock ;

/* Variables and functions */
#define  BHND_CLOCK_DYN 129 
#define  BHND_CLOCK_HT 128 
 int /*<<< orphan*/  CHIPC_PLL_DELAY ; 
 int /*<<< orphan*/  CHIPC_PLL_SLOWCLK_CTL ; 
 int CHIPC_SCC_FS ; 
 int CHIPC_SCC_IP ; 
 int CHIPC_SCC_SS_MASK ; 
 int CHIPC_SCC_SS_XTAL ; 
 int CHIPC_SCC_XC ; 
 int CHIPC_SYCC_HR ; 
 int /*<<< orphan*/  CHIPC_SYS_CLK_CTL ; 
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  FIXED_CLK ; 
 int /*<<< orphan*/  INSTACLK_CTL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PWRCTL_LOCK_ASSERT (struct bhnd_pwrctl_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ PWRCTL_QUIRK (struct bhnd_pwrctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOWCLK_CTL ; 
 int bhnd_bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_pwrctl_hostb_gate_clock (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  bhnd_pwrctl_hostb_ungate_clock (int /*<<< orphan*/ ,int const) ; 

int
bhnd_pwrctl_setclk(struct bhnd_pwrctl_softc *sc, bhnd_clock clock)
{
	uint32_t	scc;

	PWRCTL_LOCK_ASSERT(sc, MA_OWNED);

	/* Is dynamic clock control supported? */
	if (PWRCTL_QUIRK(sc, FIXED_CLK))
		return (ENODEV);

	/* Chips with ccrev 10 are EOL and they don't have SYCC_HR used below */
	if (bhnd_get_hwrev(sc->chipc_dev) == 10)
		return (ENODEV);

	if (PWRCTL_QUIRK(sc, SLOWCLK_CTL))
		scc = bhnd_bus_read_4(sc->res, CHIPC_PLL_SLOWCLK_CTL);
	else
		scc = bhnd_bus_read_4(sc->res, CHIPC_SYS_CLK_CTL);

	switch (clock) {
	case BHND_CLOCK_HT:
		/* fast (pll) clock */
		if (PWRCTL_QUIRK(sc, SLOWCLK_CTL)) {
			scc &= ~(CHIPC_SCC_XC | CHIPC_SCC_FS | CHIPC_SCC_IP);
			scc |= CHIPC_SCC_IP;

			/* force xtal back on before clearing SCC_DYN_XTAL.. */
			bhnd_pwrctl_hostb_ungate_clock(sc->chipc_dev,
			    BHND_CLOCK_HT);
		} else if (PWRCTL_QUIRK(sc, INSTACLK_CTL)) {
			scc |= CHIPC_SYCC_HR;
		} else {
			return (ENODEV);
		}

		if (PWRCTL_QUIRK(sc, SLOWCLK_CTL))
			bhnd_bus_write_4(sc->res, CHIPC_PLL_SLOWCLK_CTL, scc);
		else
			bhnd_bus_write_4(sc->res, CHIPC_SYS_CLK_CTL, scc);
		DELAY(CHIPC_PLL_DELAY);

		break;		

	case BHND_CLOCK_DYN:
		/* enable dynamic clock control */
		if (PWRCTL_QUIRK(sc, SLOWCLK_CTL)) {
			scc &= ~(CHIPC_SCC_FS | CHIPC_SCC_IP | CHIPC_SCC_XC);
			if ((scc & CHIPC_SCC_SS_MASK) != CHIPC_SCC_SS_XTAL)
				scc |= CHIPC_SCC_XC;
	
			bhnd_bus_write_4(sc->res, CHIPC_PLL_SLOWCLK_CTL, scc);

			/* for dynamic control, we have to release our xtal_pu
			 * "force on" */
			if (scc & CHIPC_SCC_XC) {
				bhnd_pwrctl_hostb_gate_clock(sc->chipc_dev,
				    BHND_CLOCK_HT);
			}
		} else if (PWRCTL_QUIRK(sc, INSTACLK_CTL)) {
			/* Instaclock */
			scc &= ~CHIPC_SYCC_HR;
			bhnd_bus_write_4(sc->res, CHIPC_SYS_CLK_CTL, scc);
		} else {
			return (ENODEV);
		}

		break;

	default:
		return (ENODEV);
	}

	return (0);
}