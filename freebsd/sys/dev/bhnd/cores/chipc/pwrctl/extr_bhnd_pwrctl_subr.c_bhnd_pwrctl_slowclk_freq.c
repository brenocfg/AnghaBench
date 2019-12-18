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
struct bhnd_pwrctl_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  res; } ;
typedef  int bhnd_clksrc ;

/* Variables and functions */
#define  BHND_CLKSRC_LPO 130 
#define  BHND_CLKSRC_PCI 129 
#define  BHND_CLKSRC_XTAL 128 
 int CHIPC_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int CHIPC_LPOMAXFREQ ; 
 int CHIPC_LPOMINFREQ ; 
 int CHIPC_PCIMAXFREQ ; 
 int CHIPC_PCIMINFREQ ; 
 int /*<<< orphan*/  CHIPC_PLL_SLOWCLK_CTL ; 
 int /*<<< orphan*/  CHIPC_SCC_CD ; 
 int /*<<< orphan*/  CHIPC_SYCC_CD ; 
 int /*<<< orphan*/  CHIPC_SYS_CLK_CTL ; 
 int CHIPC_XTALMAXFREQ ; 
 int CHIPC_XTALMINFREQ ; 
 int /*<<< orphan*/  INSTACLK_CTL ; 
 int /*<<< orphan*/  PCICLK_CTL ; 
 scalar_t__ PWRCTL_QUIRK (struct bhnd_pwrctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOWCLK_CTL ; 
 int bhnd_bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_pwrctl_slowclk_src (struct bhnd_pwrctl_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static uint32_t
bhnd_pwrctl_slowclk_freq(struct bhnd_pwrctl_softc *sc, bool max_freq)
{
	bhnd_clksrc	slowclk;
	uint32_t	div;
	uint32_t	hz;

	slowclk = bhnd_pwrctl_slowclk_src(sc);

	/* Determine clock divisor */
	if (PWRCTL_QUIRK(sc, PCICLK_CTL)) {
		if (slowclk == BHND_CLKSRC_PCI)
			div = 64;
		else
			div = 32;
	} else if (PWRCTL_QUIRK(sc, SLOWCLK_CTL)) {
		div = bhnd_bus_read_4(sc->res, CHIPC_PLL_SLOWCLK_CTL);
		div = CHIPC_GET_BITS(div, CHIPC_SCC_CD);
		div = 4 * (div + 1);
	} else if (PWRCTL_QUIRK(sc, INSTACLK_CTL)) {
		if (max_freq) {
			div = 1;
		} else {
			div = bhnd_bus_read_4(sc->res, CHIPC_SYS_CLK_CTL);
			div = CHIPC_GET_BITS(div, CHIPC_SYCC_CD);
			div = 4 * (div + 1);
		}
	} else {
		device_printf(sc->dev, "unknown device type\n");
		return (0);
	}

	/* Determine clock frequency */
	switch (slowclk) {
	case BHND_CLKSRC_LPO:
		hz = max_freq ? CHIPC_LPOMAXFREQ : CHIPC_LPOMINFREQ;
		break;
	case BHND_CLKSRC_XTAL:
		hz = max_freq ? CHIPC_XTALMAXFREQ : CHIPC_XTALMINFREQ;
		break;
	case BHND_CLKSRC_PCI:
		hz = max_freq ? CHIPC_PCIMAXFREQ : CHIPC_PCIMINFREQ;
		break;
	default:
		device_printf(sc->dev, "unknown slowclk source %#x\n", slowclk);
		return (0);
	}

	return (hz / div);
}